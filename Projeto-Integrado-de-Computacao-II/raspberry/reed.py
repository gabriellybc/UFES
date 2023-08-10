import time
import RPi. GPIO as GPIO
from config import REED_SENSOR_PIN

def setup():
    GPIO.setup(REED_SENSOR_PIN, GPIO.IN, pull_up_down=GPIO.PUD_UP)

def get_input():
    input_reed=0.0
    for i in range(20):
        input_reed += GPIO.input(REED_SENSOR_PIN)
    input_reed /=20
    if input_reed > 0.5:
        input_reed = 1
    else:
        input_reed = 0
     
    return input_reed

def main():
    GPIO.setmode(GPIO.BCM)
    setup()
    while True:
        input_reed = get_input()
        print(input_reed)
        time.sleep(1)

if __name__ == '__main__':
    main()
