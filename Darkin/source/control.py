# build state space
import random
import time

import numpy as np
import statsmodels.api as sm
import keyboard
import pyautogui

Q = 0x10
W = 0x11
E = 0x12
R = 0x13
A = 0x1E
S = 0x1F
D = 0x20
F = 0x21
B = 0x30
CONTROL = 0x2D
TAB = 0x0F
SPACE = 0x39
ENTER = 0x1C
key1 = 0x02
key2 = 0x03
key3 = 0x04
key4 = 0x05
key5 = 0x06
key6 = 0x07
key7 = 0x08
center = (pyautogui.size()[0] / 2, pyautogui.size()[1] / 2 - 50)

print(pyautogui.size())

Q1 = 475
Q2 = 350
Q3 = 175
E_dash = range(0, 360)


# implement league of legends actions
def press_key(key):
    pyautogui.keyDown(key)


def release_key(key):
    pyautogui.keyUp(key)


def press_key_and_release(key):
    pyautogui.press(key)


def auto_attack():
    pyautogui.keyDown('a')
    # right click
    pyautogui.click(button='right')
    pyautogui.keyUp('a')


def move_down():
    pyautogui.moveTo(center[0], center[1] + 100)
    pyautogui.click(button='right')
    pyautogui.mouseUp(button='right')


def move_up():
    pyautogui.moveTo(center[0], center[1] - 100)
    pyautogui.click(button='right')
    pyautogui.mouseUp(button='right')


def move_left():
    pyautogui.moveTo(center[0] - 100, center[1])
    pyautogui.click(button='right')
    pyautogui.mouseUp(button='right')


def move_right():
    pyautogui.moveTo(center[0] + 100, center[1])
    pyautogui.click(button='right')
    pyautogui.mouseUp(button='right')


def move_angel(angel):
    pyautogui.moveTo(center[0] + 100 * np.cos(angel), center[1] + 100 * np.sin(angel))
    pyautogui.click(button='right')
    pyautogui.mouseUp(button='right')


def cast_q_toward(angle):
    pyautogui.moveTo(center[0] + 100 * np.cos(angle), center[1] + 100 * np.sin(angle))
    keyboard.press_and_release('q')


def cast_w_toward(angle):
    pyautogui.moveTo(center[0] + 100 * np.cos(angle), center[1] + 100 * np.sin(angle))
    keyboard.press_and_release('w')


def cast_q_toward_target(phase, angle):
    if phase == 1:
        pyautogui.moveTo(center[0] + Q1 * np.cos(angle), center[1] + Q1 * np.sin(angle))
        keyboard.press_and_release('q')
    elif phase == 2:
        pyautogui.moveTo(center[0] + Q2 * np.cos(angle), center[1] + Q2 * np.sin(angle))
        keyboard.press_and_release('q')
    elif phase == 3:
        pyautogui.moveTo(center[0] + Q3 * np.cos(angle), center[1] + Q3 * np.sin(angle))
        keyboard.press_and_release('q')
    time.sleep(1.2)


time.sleep(5)
for i in range(10):
    for angle in range(0, 360, 36):
        cast_q_toward_target(1, angle)
        cast_q_toward_target(2, angle)
        cast_q_toward_target(3, angle)
        time.sleep(1.5)




