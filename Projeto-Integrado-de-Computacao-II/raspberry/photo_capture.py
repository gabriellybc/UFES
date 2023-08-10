import cv2
import time
import keyboard
import recognizer
import RPi.GPIO as GPIO
from config import POTHO_PATH, WAITING_TIME, DEBOUNCE_TIME

def take_photo():
    """Display webcam video and capture photo."""
    cap = cv2.VideoCapture(0)
    time_start = time.time()
    time_end = time.time()

    while True:
        ret, frame = cap.read()
        if frame is None:
            continue
        time_end = time.time()

        height, width, _ = frame.shape
        message = "Fique olhando para a camera e espere 5 segundos"
        font = cv2.FONT_HERSHEY_SIMPLEX
        font_scale = 0.5
        thickness = 1
        text_size, _ = cv2.getTextSize(message, font, font_scale, thickness)
        x = 10
        y = height - text_size[1] - 10

        cv2.rectangle(frame, (x - 4, y - 4), (x + text_size[0] + 4, y + text_size[1] + 4), (0, 0, 0), -1)
        cv2.putText(frame, message, (x, y + text_size[1]), font, font_scale, (255, 255, 255), thickness, cv2.LINE_AA)
        cv2.imshow("Webcam", frame)

        key = cv2.waitKey(1)

        if (time_end - time_start) >= WAITING_TIME or key == ord('2'):
            cv2.imwrite(POTHO_PATH, frame)
            cap.release()
            cv2.destroyAllWindows()
            break

def show_photo():
    """Display captured photo and get response."""
    img = cv2.imread(POTHO_PATH)
    height, width, _ = img.shape
    message = "Espere 5 segundo ou aperte 2 para continuar ou 3 para tirar outra foto."
    font = cv2.FONT_HERSHEY_SIMPLEX
    font_scale = 0.5
    thickness = 1
    text_size, _ = cv2.getTextSize(message, font, font_scale, thickness)
    x = 10
    y = height - text_size[1] - 10

    cv2.rectangle(img, (x - 4, y - 4), (x + text_size[0] + 4, y + text_size[1] + 4), (0, 0, 0), -1)
    cv2.putText(img, message, (x, y + text_size[1]), font, font_scale, (255, 255, 255), thickness, cv2.LINE_AA)
    cv2.imshow("Captured Photo", img)

def get_response():
    """Get response."""
    time_start = time.time()
    time_end = time.time()
    key = None
    while True:
            time.sleep(DEBOUNCE_TIME)
            key2 = cv2.waitKey(1)
            time_end = time.time()
            key = keyboard.keypad()

            if key == '2' or key == '3' or (time_end - time_start) >= WAITING_TIME or key2 == ord('2'):
                cv2.destroyAllWindows()
                return key


def main() -> bool:
    """Main function."""
    take_photo()
    show_photo()
    response = get_response()

    if response == "2" or response is None:
        print("Foto aceita!")
        return True

    elif response == "3":
        print("Tirando outra foto...")
        main()

if __name__ == '__main__':
    # GPIO.setmode(GPIO.BCM)
    # keyboard.setup()
    main()