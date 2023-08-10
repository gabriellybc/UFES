import paho.mqtt.client as mqtt
import requests
import os

from config import OWNER, HOSTNAME


def main():
    """Main function of the MQTT client"""
    # MQTT client configuration
    client = mqtt.Client()

    # Definition of callback functions
    client.on_connect = on_connect
    client.on_message = on_message

    # Connection to the MQTT broker
    broker = HOSTNAME
    porta = 1883 
    client.connect(broker, porta)

    # Loop to maintain connection and process incoming messages
    try:
        client.loop_forever()
    except KeyboardInterrupt:
        print("Interrupção da conexão com o broker MQTT")
        client.disconnect()


def on_connect(client, userdata, flags, rc):
    """Callback that will be executed when the connection with the MQTT broker is established"""
    if rc == 0:
        print("Conexão bem-sucedida MQTT")
        client.subscribe(f"ssmai/encodings/{OWNER}")
    else:
        print(f"Falha na conexão. Código de retorno: {rc}")


def on_message(client, userdata, msg):
    """Callback that will be executed when the message is published successfully"""
    message = str(msg.payload.decode())
    print(message)
    messages = message.split(": ")
    filename = messages[1]
    if messages[0] == "ADDED":
        get_encoding(filename)
    elif messages[0] == "DELETED":
        delete_encoding(filename)
    else:
        print("Mensagem inválida.")


def get_encoding(filename):
    """Download the encoding file from the server"""
    url = f"http://{HOSTNAME}:8000/encoding/{filename}/"
    path = f"./encoding/{filename}.pkl"

    response = requests.get(url, stream=True)

    if response.status_code == 200:
        with open(path, "wb") as file:
            file.write(response.content)
        print("Arquivo baixado e salvo com sucesso.")
    else:
        print("Falha ao baixar o arquivo.")


def delete_encoding(filename):
    """Delete the encoding file from the server"""
    path = f"./encoding/{filename}.pkl"
    try:
        os.remove(path)
        print("Arquivo removido com sucesso.")
    except FileNotFoundError:
        print("Arquivo não encontrado.")


if __name__ == "__main__":
    main()
