# Backend Django

## Passos para rodar o backend:

1. Só faça uma vez se ainda não tiver o pacote venv, rode: ``` sudo apt install python3.8-venv ```

1. Dê um nome e crie o ambiente virtual. Exemplo para criação do ambiente virtual de nome .env: ``` python3.8 -m venv .env ```

1. **Ative o ambiente virtual usando** (sempre faça esse passo antes de rodar código): ``` source .env/bin/activate ```

1. Instale as bibliotecas do requirements no seu ambiente virtual usando: ``` pip install -U -r requirements.txt ```

1. Rode o servidor: ``` python manage.py runserver ```

## Outros comandos importantes:

- Criar um projeto Django: ``` django-admin startproject nome_projeto . ```

- Dentro do um projeto, criar uma aplicação Django: ``` django-admin startapp nome_app ```

- Pegar todas as aplicações existentes em um projeto Django e criar migrations para elas: ``` python manage.py makemigrations ```

- Mandar o Djang executar as migrations: ``` python manage.py migrate ```

- Criar conta de administrador: ``` python manage.py createsuperuser ```

- Importando pacote estático: ``` python manage.py collectstatic ```