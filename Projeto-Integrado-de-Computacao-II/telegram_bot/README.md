# Bot Telegram Cadastro

### Passos para rodar o Bot do Telegram que faz o Cadastro:

1. Só faça uma vez se ainda não tiver o pacote venv, rode: ``` sudo apt install python3.8-venv ```

1. Dê um nome e crie o ambiente virtual. Exemplo para criação do ambiente virtual de nome .env: ``` python3.8 -m venv .env ```

1. **Ative o ambiente virtual usando** (sempre faça esse passo antes de rodar código): ``` source .env/bin/activate ```

1. Instale as bibliotecas do requirements no seu ambiente virtual usando: ``` pip install -U -r requirements.txt ```

1. Rode o seu arquivo de código principal: ``` python telegram_bot.py ```