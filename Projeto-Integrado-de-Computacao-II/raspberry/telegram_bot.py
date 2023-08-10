import logging
import asyncio
import threading
import os
import sys

from telegram import Update, Bot
from telegram.ext import ApplicationBuilder, CommandHandler, ContextTypes

from config import TOKEN, POTHO_PATH


args = sys.argv

logging.basicConfig(
    format='%(asctime)s - %(name)s - %(levelname)s - %(message)s',
    level=logging.INFO
)

application = ApplicationBuilder().token(TOKEN).build()


def main():
    """Run the bot."""
    thread = threading.Thread(target=my_thread)
    thread.start()
    thread.join()

    sim_handler = CommandHandler('sim', sim)
    nao_handler = CommandHandler('nao', nao)

    application.add_handler(sim_handler)
    application.add_handler(nao_handler)
        
    application.run_polling()


def my_thread():
    """Function that runs in a separate thread"""
    person = args[1]
    chat_id = args[2]
    asyncio.run(send_message(chat_id, person))


async def send_message(chat_id: str, person: str):
    """Asynchronously sends a message with a photo"""
    bot = Bot(token=TOKEN)
    
    await bot.send_photo(chat_id=chat_id, photo=open(POTHO_PATH, 'rb'))

    person = "Essa pessoa" if person == "unknown" else person
    mensagem = f"{person} deseja entrar. Você permite sua entrada?\n\n- Mande /sim para ABRIR portão\n- Mande /nao para manter o portão FECHADO"
    await bot.send_message(chat_id=chat_id, text=mensagem)


async def sim(update: Update, context: ContextTypes.DEFAULT_TYPE):
    """Handler function for the /sim command"""
    text = "Você mandou SIM. O portão será ABERTO"
    await context.bot.send_message(chat_id=update.effective_chat.id, text=text)
    os._exit(0)


async def nao(update: Update, context: ContextTypes.DEFAULT_TYPE):
    """Handler function for the /nao command"""
    text = "Você mandou NÃO. O portão ficará FECHADO"
    await context.bot.send_message(chat_id=update.effective_chat.id, text=text)
    os._exit(1)


if __name__ == '__main__':
    main()