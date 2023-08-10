import os
import cv2
import time
import RPi. GPIO as GPIO
import photo_capture
import recognizer
import keyboard
import reed
import gate
from gpiozero import DistanceSensor, LED, Buzzer, Button
from config import TRIG_PIN, ECHO_PIN, MAX_DISTANCE, MIN_DISTANCE, QNTD_RECOGNIZE, WAITING_TIME, SYSTEM_PASSWORD, SECURITY_PASSWORD, RED_LED_PIN, GREEN_LED_PIN, TIME_BLINK, BUZZER_PIN, BUTTON_PIN, OPEN_TIME, DEBOUNCE_TIME


GPIO.setmode(GPIO.BCM)
ultrasonic = DistanceSensor(echo=ECHO_PIN, trigger=TRIG_PIN)
keyboard.setup()
button = Button(BUTTON_PIN)
led_red = LED(RED_LED_PIN)
led_green = LED(GREEN_LED_PIN)
buzzer = Buzzer(BUZZER_PIN)
reed.setup()
gate.setup()


def main():
    """Main function."""
    button.when_pressed = open_gate

    while True:
        os.system('clear')
        if not reed.get_input():
            print("porta Aberta")
        while not reed.get_input():
            led_green.on()
        if reed.get_input():
            led_green.off()
        display()
        response = keyboard.get_char()
        time.sleep(DEBOUNCE_TIME)
        print("Opção selecionada:	", response)

        if response == '1':
            os.system('clear')
            print("\nIniciando processo de reconhecimento facial...")
            recognizer_face()
        elif response == '2':
            os.system('clear')
            print("\nDigite a senha: ")
            password()
        elif response == '3':
            os.system('clear')
            print("\nDigite a senha segura: ")
            get_new_password()
        else:
            print("\nOpção inválida!")
            time.sleep(DEBOUNCE_TIME)
            continue


def display():
    """Displays"""
    os.system('clear')
    print("\n")
    print("\n")
    print("Digite uma opção: ")
    print("\n")
    print("1 - Entrar com Reconhecimento Facial")
    print("\n")
    print("2 - Entrar com Senha")
    print("\n")
    print("3 - Alterar Senha")
    print("\n")
    print("\n")


def recognizer_face():
    time_start = time.time()
    have_person = 0
    while True:
        distance = round(ultrasonic.distance * 100)

        if time.time() - time_start > WAITING_TIME*3:
            print("\nTempo de espera esgotado!")
            not_open_gate()
            break

        if distance > MAX_DISTANCE:
            print(f"\nAproxime-se do sensor.\nA distância máxima é {MAX_DISTANCE}cm. \nDistancia atual: {distance}cm\n\n")
            time.sleep(WAITING_TIME)
            have_person = 0
        elif distance < MIN_DISTANCE:
            print(f"\nAfaste-se do sensor. \nA distância minima é {MIN_DISTANCE}cm. \nDistancia atual: {distance}cm\n\n")
            time.sleep(WAITING_TIME)
        elif distance <= MAX_DISTANCE:
            have_person += 1
            print(f"\nPerfeito! Você detectado(a) a {distance}cm")
            time.sleep(WAITING_TIME)
            time_start = time.time()
        
        if have_person >= QNTD_RECOGNIZE:
            os.system('clear')
            have_person = 0

            print("\nIniciando processo de tirar foto...")
            take_photo = photo_capture.main()
            
            if take_photo:
                print("\nIniciando processo de reconhecimento...")
                open_gate_flag = recognizer.main()
                if open_gate_flag:
                        print("\nAbrir Portão!")
                        open_gate()
                        break
                else:
                    print("\nNão Abrir!")
                    not_open_gate()
                    break



def get_password() -> str:
    characters = ""
    while True:
        char = keyboard.get_char()
        time.sleep(DEBOUNCE_TIME)
        if char == "#":
            break
        characters += char

        os.system('clear')
        print("\nTermine de digitar a senha e pressione # para confirmar.")
    return characters


def get_new_password():
    characters = get_password()
    
    print("\nSenha digitada!")
    
    if characters == SECURITY_PASSWORD:
        characters = ""
        os.system('clear')
        print("\nSenha segura certa!")

        print("\nDigite a nova senha com mais de 3 digitos: ")
        characters = get_password()
        if len(characters) <= 3 or (all(char == characters[0] for char in characters)):
            os.system('clear')
            print("\nSenha digitada!")
            print("\nSenha não alterada!\nA senha deve ter mais de 3 digitos e não deve ter todos os caracteres iguais!")
            not_open_gate()
        else:
            os.system('clear')
            print("\nDigite novamente a mesma senha para confirmar: ")
            characters_confirm = get_password()
            if characters != characters_confirm:
                os.system('clear')
                print("\nSenha digitada!")
                print("\nSenha não alterada!\nAs senhas não conferem!")
                not_open_gate()
            else:
                os.system('clear')
                print("\nSenha digitada!")
                global SYSTEM_PASSWORD
                file = open("config.py", "r+")
                lines = file.readlines()
                lines[0] = f'SYSTEM_PASSWORD = "{characters_confirm}"\n'
                file.seek(0)
                file.writelines(lines)
                file.close()
                SYSTEM_PASSWORD = characters_confirm
                print("\nSenha segura alterada com sucesso!")
                blink_led_buzzer(led_green)

    else:
        characters = ""
        print("Senha errada!")
        not_open_gate()


def password():
    characters = get_password()
    
    print("\nSenha digitada!")
    
    if characters == SYSTEM_PASSWORD:
        characters = ""
        print("Senha certa!")
        open_gate()
    else:
        characters = ""
        print("Senha errada!")
        not_open_gate()


def close_gate():
    """Close gate"""
    led_green.on()
    time_of_change = time.time()
    print("\nArguardando o Potão ser Fechado!")
    while reed.get_input():
        a=1        
    print("\nPortão fechado!")
    led_green.off()
    


def open_gate():
    """Open gate"""
    while reed.get_input():
        print("\nAbrir Portão!")
        gate.open_door()
        close_gate()
    else:
        print("\nPortão já está aberto!")
        blink_led(led_red)


def not_open_gate():
    """Not open gate"""
    print("\nNão Abrir!")
    blink_led_buzzer(led_red)


def blink_led(led):
    """Blink led"""
    time_start = time.time()
    while (time.time() - time_start) < TIME_BLINK:
        led.blink()
    led.off()


def blink_led_buzzer(led):
    """Blink led"""
    time_start = time.time()
    while (time.time() - time_start) < TIME_BLINK:
        led.blink()
        buzzer.beep()
    led.off()
    buzzer.off()


try:
    main()
except KeyboardInterrupt:
    GPIO.cleanup()
