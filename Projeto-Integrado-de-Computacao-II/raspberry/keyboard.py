import time
import RPi.GPIO as GPIO
from config import ROW_PINS, COL_PINS, KEY_MATRIX, DEBOUNCE_TIME

def setup():
    for x in range(0, 4):
        GPIO.setup(ROW_PINS[x], GPIO.OUT)
        GPIO.output(ROW_PINS[x], GPIO.HIGH)

    for x in range(0, 3):
        GPIO.setup(COL_PINS[x], GPIO.IN, pull_up_down=GPIO.PUD_UP)

def keypad(col=COL_PINS, row=ROW_PINS):
    for r in row:
        GPIO.output(r, GPIO.LOW)
        result = [GPIO.input(col[0]), GPIO.input(col[1]), GPIO.input(col[2])]
        if min(result) == 0:
            key = KEY_MATRIX[int(row.index(r))][int(result.index(0))]
            GPIO.output(r, GPIO.HIGH)
            return key
        GPIO.output(r, GPIO.HIGH)

def get_char():
    while True:
        key = keypad(COL_PINS, ROW_PINS)
        if key is not None:
            return key

def main():
    GPIO.setmode(GPIO.BCM)
    setup()
    key = get_char()
    print(key)

if __name__ == '__main__':
    main()