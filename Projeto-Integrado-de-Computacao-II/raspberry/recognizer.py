import os
import subprocess
import requests

import numpy as np
import face_recognition
import pickle

from config import OWNER, POTHO_PATH, HOSTNAME


def main() -> bool:
    """Main function of the recognizer"""
    known_faces_dir = "./encoding/"
    if not os.path.exists(known_faces_dir):
        os.makedirs(known_faces_dir)
    known_faces = save_encodings_dict(known_faces_dir)
    identifier = recognize_unknown(known_faces, tolerance=0.6)
    open_gate = identify_person(identifier)
    return open_gate


def save_encodings_dict(known_faces_dir: str) -> dict:
    """Runs through all encodings to save in a dictionary"""
    known_faces = {}
    for filename in os.listdir(known_faces_dir):
        encoding = load_encoding(known_faces_dir, filename)
        person_identifier = filename.split("--")[0]
        if person_identifier not in known_faces:
            known_faces[person_identifier] = []
        known_faces[person_identifier].append(encoding)
    return known_faces


def generate_encodings(path: str) -> list:
    """Generates encodings from a photo"""
    image = face_recognition.load_image_file(path, mode='RGB')
    encodings = face_recognition.face_encodings(image)
    return encodings


def load_encoding(path: str, filename: str):
    """Loads encoding from pickle format"""
    encoding = pickle.load(open(path+filename, 'rb'))
    return encoding


def recognize_unknown(known_faces: dict, tolerance: float = 0.6) -> str:
    """Takes a photo and recognizes the unknown person"""
    unknown_face_encodings = generate_encodings(POTHO_PATH)
    if len(unknown_face_encodings) == 0:
        print(f"Nenhuma face encontrada na imagem!")
        return False
    
    print("Percorrendo todas as codificações faciais na imagem desconhecida")
    found_match = False
    for unknown_face_encoding in unknown_face_encodings:

        for identifier, face_encodings in known_faces.items():
            matches = face_recognition.compare_faces(face_encodings, unknown_face_encoding, tolerance=tolerance)

            if np.any(matches):
                print("Encontrado correspondência!!!")
                found_match = True
                print(f"Pessoa identificada: {identifier}")

                average_distance = np.average(face_recognition.face_distance(face_encodings, unknown_face_encoding))
                print(f"Tem uma distância média de  {round(average_distance, 3)}")
                return identifier

    if not found_match:
        print("Esta pessoa não é reconhecida.")
        return "unknown"


def identify_person(identifier) -> bool:
    """Identify the person"""
    if identifier == "unknown":
        print("Esta é a imagem de uma pessoa desconhecida!")

    elif not identifier:
        print("Nenhuma face encontrada na imagem!")
        open_gate = False
        return open_gate

    else:
        guest = get_guest(identifier)
        if "fail" in guest:
            identifier = guest["fail"]
        else:
            identifier = ""
            if guest["relationship"] != None and guest["relationship"] != "" and guest["relationship"] != " ":
                identifier = f"Seu/Sua {guest['relationship']} "
            if guest["nickname"] != None and guest["nickname"] != "" and guest["nickname"] != " ":
                identifier += f"{guest['nickname']}"
            else:
                identifier += f"{guest['name']}"

    print(f"This is the image of {identifier}!")

    owner = get_owner()
    if "fail" in owner:
        print(owner["fail"])
        open_gate = False
    else:
        print("Opening Telegram Bot")
        open_gate = run_telegram_bot(identifier, owner["chat_id"])
    return open_gate



def get_guest(identifier):
    """Get the guest's infos from the server"""
    url = f"http://{HOSTNAME}:8000/guest/json/{identifier}/" 
    response = requests.get(url)
    data = {}
    if response.status_code == 200:
        data = response.json()
    else:
        data["fail"] = "Falha ao obter informações"
    return data


def get_owner():
    """Get the guest's infos from the server"""
    url = f"http://{HOSTNAME}:8000/owner/json/{OWNER}/" 
    response = requests.get(url)
    data = {}
    if response.status_code == 200:
        data = response.json()
    else:
        data["fail"] = "Falha ao obter informações"
    return data


def run_telegram_bot(person, chat_id) -> bool:
    """Run Telegram Bot to send the photo of the person you want to enter. Ask the owner if you can open the gate or not"""
    command = ["python", "telegram_bot.py", person, chat_id]
    result = subprocess.run(command, capture_output=True, text=True)
    open_gate = False
    if result.returncode == 0:
        print("Abrir Portão")
        open_gate = True
    elif result.returncode == 1:
        print("Manter Portão Fechado")
        open_gate = False
    else:
        print("Error:")
        print(result.stderr)
    return open_gate



if __name__ == "__main__":
    main()
