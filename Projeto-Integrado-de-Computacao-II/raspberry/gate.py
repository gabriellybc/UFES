import time
import RPi. GPIO as GPIO
from config import GATE, DELAY_GATE

def setup():
    GPIO.setup(GATE, GPIO.OUT)
    GPIO.output(GATE, GPIO.HIGH)

def open_door():
    GPIO.output(GATE, GPIO.LOW)
    time.sleep(DELAY_GATE)
    GPIO.output(GATE, GPIO.HIGH)

def main():
    GPIO.setmode(GPIO.BCM)
    setup()
    try:
        open_door()
        time.sleep(5)  # Keeps the door open for 5 seconds
    finally:
        GPIO.cleanup()

if __name__ == '__main__':
    main()