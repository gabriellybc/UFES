import logging
import os
import requests

from telegram import Update
from telegram.ext import filters, MessageHandler, ApplicationBuilder, CommandHandler, ContextTypes

HOSTNAME = "10.9.10.17"
TOKEN = '6108504715:AAGnfS26xOpHLsu-TZ1NXzRyzHMWo73Ohhk'

logging.basicConfig(
    format='%(asctime)s - %(name)s - %(levelname)s - %(message)s',
    level=logging.INFO
)

application = ApplicationBuilder().token(TOKEN).build()


def main():
    start_handler = CommandHandler('start', start)
    get_message_handler = MessageHandler(filters.TEXT & (~filters.COMMAND), get_message)

    application.add_handler(start_handler)
    application.add_handler(get_message_handler)
        
    application.run_polling()


async def start(update: Update, context: ContextTypes.DEFAULT_TYPE):
    """Handler function for the /start command"""
    name = update.message.from_user.first_name
    text=f"{name}, informe o seu e-mail para ser cadastrado no sistema"
    await context.bot.send_message(chat_id=update.effective_chat.id, text=text)


async def get_message(update: Update, context: ContextTypes.DEFAULT_TYPE):
    """Handler function for text messages"""
    chat_id = update.effective_chat.id
    email_received = update.message.text.strip().replace(" ", "").lower()
    text = set_chat_id(email_received, chat_id)
    await context.bot.send_message(chat_id=chat_id, text=text)


def set_chat_id(email: str, chat_id: str) -> str:
    """Set the chat_id"""
    url = f'http://{HOSTNAME}:8000/owner/json/{email}/'  
    data = {
        'chat_id': chat_id
    }
    response = requests.post(url, data=data)

    if response.status_code == 200:
        if response.text == "Chat ID salvo com sucesso":
            return "Você foi cadastrado(a) com sucesso!"
        elif response.text == "Chat ID ja cadastrado":
            return "Telegram já cadastrado! Se deseja trocar de conta do Telegram, entre em contato com a nossa equipe."
    else:
        return "E-mail inválido. Tente novamente"


if __name__ == '__main__':
    main()