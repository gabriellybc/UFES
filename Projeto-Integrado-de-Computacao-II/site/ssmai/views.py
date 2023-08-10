import os
from django.conf import settings
from django.shortcuts import render, redirect, get_object_or_404
from django.contrib import messages
from django.shortcuts import redirect
from django.http import HttpResponse, JsonResponse
from django.views.decorators.csrf import csrf_exempt

from .models import Hospede, Acesso, CustomUser


def index(request):
    return render(request, 'index.html', {})


def encoding(request, filename):
    try:
        encoding_path = os.path.join(settings.MEDIA_ROOT, 'encoding', f'{filename}.pkl')

        if os.path.exists(encoding_path):
            with open(encoding_path, 'rb') as file:
                response = HttpResponse(file.read(), content_type='application/octet-stream')
                response['Content-Disposition'] = f'attachment; filename="{filename}.pkl"'
                return response
        else:
            messages.error(request, 'O arquivo de encoding não existe.')
            return redirect('index')
    except Exception:
        messages.error(request, 'Ocorreu um erro durante o download do arquivo.')
        return redirect('index')


def guest_json(request, phone):
    guest = get_object_or_404(Hospede, phone=phone)
    if guest:
        guest_data = {
            'name': guest.name,
            'phone': guest.phone,
            'nickname': guest.nickname,
            'relationship': guest.relationship,
            'owner': guest.owner.email
        }
        access = Acesso(guest=guest)
        access.save()
        return JsonResponse(guest_data)
    else:
        return HttpResponse('Hospede não encontrado.')


@csrf_exempt
def owner_json(request, email):
    owner = get_object_or_404(CustomUser, email=email)
    if owner:
        if request.method == 'POST':
            chat_id = request.POST.get('chat_id')
            if owner.first_access:
                owner.chat_id = chat_id
                owner.first_access = False
                owner.save()
                return HttpResponse('Chat ID salvo com sucesso')
            else:
                if owner.chat_id == chat_id:
                    return HttpResponse('Chat ID salvo com sucesso')
                else:
                    return HttpResponse('Chat ID ja cadastrado')

        owner_data = {
            'name': owner.get_full_name(),
            'email': owner.email,
            'first_access': owner.first_access,
            'chat_id': owner.chat_id
        }
        return JsonResponse(owner_data)
    else:
        return HttpResponse('Proprietário(a) não encontrado.')


def telegram(request):
    return render(request, 'telegram.html', {})