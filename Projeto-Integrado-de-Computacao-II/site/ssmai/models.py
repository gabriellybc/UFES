from django.db import models
from stdimage.models import StdImageField
from django.db.models import signals
from django.template.defaultfilters import slugify
from django.contrib.auth.models import AbstractUser, BaseUserManager
from django.contrib.auth import get_user_model

import os
from paho.mqtt import publish
from .encodings import generate_encodings, save_encoding, delete_encoding

HOSTNAME = "10.9.10.17"

class CustomUserManager(BaseUserManager):

    use_in_migrations = True

    def _create_user(self, email, password, **extra_fields):
        if not email or len(email) < 5 or '@' not in email or '.' not in email:
            raise ValueError('O e-mail é obrigatório e deve ser válido!')
        email = self.normalize_email(email)
        user = self.model(email=email, username=email, **extra_fields)
        user.set_password(password)
        user.save(using=self._db)
        return user

    def create_user(self, email, password=None, **extra_fields):
        extra_fields.setdefault('is_staff', True)
        extra_fields.setdefault('is_superuser', False)
        return self._create_user(email, password, **extra_fields)

    def create_superuser(self, email, password, **extra_fields):
        extra_fields.setdefault('is_superuser', True)
        extra_fields.setdefault('is_staff', True)

        if extra_fields.get('is_superuser') is False:
            raise ValueError('Superuser precisa ter is_superuser=True')

        if extra_fields.get('is_staff') is False:
            raise ValueError('Superuser precisa ter is_staff=True')

        return self._create_user(email, password, **extra_fields)


class CustomUser(AbstractUser):
    email = models.CharField('E-mail', max_length=150, unique=True, null=False, blank=False)
    first_access = models.BooleanField('Primeiro acesso', default=True, null=False, blank=False)
    chat_id = models.CharField('Chat ID', max_length=50, null=True, blank=True)

    USERNAME_FIELD = 'email'
    REQUIRED_FIELDS = ['first_name', 'last_name']

    def __str__(self):
        return self.email

    objects = CustomUserManager()


class Base(models.Model):
    created = models.DateField('Data de criação', auto_now_add=True)
    modified = models.DateField('Data de atualização', auto_now=True)
    
    class Meta:
        abstract = True


class Hospede(Base):
    name = models.CharField('Nome', max_length=100, null=False, blank=False)
    phone = models.CharField('Telefone', max_length=11, unique=True, null=False, blank=False)
    nickname = models.CharField('Apelido', max_length=100, null=True, blank=True)
    relationship = models.CharField('Parentesco', max_length=100, null=True, blank=True)
    owner = models.ForeignKey(get_user_model(), verbose_name='Proprietário(a)', on_delete=models.CASCADE, null=False, blank=False)

    def __str__(self):
        return self.name 


class Foto(Base):
    file = StdImageField('Foto', upload_to='photo', variations={'thumb': {'width': 480, 'height': 480, 'crop': True}}, null=False, blank=False)
    slug = models.SlugField('Slug', max_length=100, blank=True, editable=False)
    guest = models.ForeignKey(Hospede, on_delete=models.CASCADE, null=False, blank=False)

    def __str__(self):
        return self.slug


class Acesso(models.Model):
    date = models.DateField('Data de acesso', auto_now_add=True)
    hour = models.TimeField('Hora de acesso', auto_now_add=True)
    guest = models.ForeignKey(Hospede, on_delete=models.CASCADE, null=False, blank=False)
    
    def __str__(self):
        return f"Acesso de {self.guest.name} em {self.data} às {self.hora} - Proprietário(a): {self.guest.owner.get_full_name()}"

    
def photo_pre_save(signal, instance, sender, **kwargs):
    instance.slug = slugify(instance.file)

signals.pre_save.connect(photo_pre_save, sender=Foto)


def photo_post_save(sender, instance, created, **kwargs):
    if created:
        path = "media/photo/"
        file_name = str(instance.file.name).replace("photo/", "")
        encodings = generate_encodings(path + str(file_name))
        if len(encodings) == 0:
            print(f"Nenhuma face encontrada na imagem {file_name}")
        filename = f"{instance.guest.phone}--{str(file_name)}"
        topic = f"ssmai/encodings/{instance.guest.owner.email}"
        message = f"ADDED: {filename}"
        save_encoding(path, filename, encodings)
        publish.single(topic, message, hostname=HOSTNAME)

signals.post_save.connect(photo_post_save, sender=Foto)


def photo_pre_delete(sender, instance, **kwargs):
    path = f"media/{instance.file.name}"
    if os.path.exists(path):
        os.remove(path)

    index = path.rfind('.')
    extension = path[index:]
    path = path[:index] + '.thumb' + extension
    if os.path.exists(path):
        os.remove(path)

    path = "media/encoding/"
    file_name = str(instance.file.name).replace("photo/", "")
    filename = f"{instance.guest.phone}--{str(file_name)}"
    topic = f"ssmai/encodings/{instance.guest.owner.email}"
    message = f"DELETED: {filename}"
    publish.single(topic, message, hostname=HOSTNAME)
    delete_encoding(path, filename)

signals.pre_delete.connect(photo_pre_delete, sender=Foto)