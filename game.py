import engine
import time

def changeLevel(nextLevel):
    global currentLevel
    currentLevel = nextLevel

from player_class import Player

player = Player() 

from main import *
from level1 import *
from level2 import *

playing = False
last_time = time.time()
currentLevel = 0


def init():  
    engine.audio.loadMusic("./asset/audio/8bit.wav")
    engine.audio.playMusic()
    

def update():
    global last_time, playing

    if currentLevel != 0:
        playing = True

    # frame calculation
    current_time = time.time()
    dt = current_time - last_time
    last_time = current_time

    if playing:
        player.update(dt)

    # level specific update
    func_name = f"update{currentLevel}"
    func = globals().get(func_name)
    if callable(func):
        func()
    else:
        print("failed calling" + func_name)

def draw():
    global gotKey
    engine.draw_map()

    # Draw player 
    player.draw()

    # level specific draw
    func_name = f"draw{currentLevel}"
    func = globals().get(func_name)
    if callable(func):
        func()   


    




