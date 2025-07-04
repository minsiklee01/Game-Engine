import engine
import time
from game import player, changeLevel

delay_timer = 0.0
timer_started = False
initiated = False
showWin = False

def init2():
    global initiated

    engine.load_tilemap("asset/map/map2.json", "asset/sprite/map/spritesheet2.png", 30, 30)
    engine.add_area2d("goal2", 550, 130, 32, 32)
    initiated = True

def update2():
    global gotKey, initiated, showWin, delay_timer, timer_started

    if not initiated:
        init2()

    if engine.is_in_area("key", int(player.x), int(player.y), int(player.w), int(player.h)):
        gotKey = True

    if engine.is_in_area("goal2", int(player.x), int(player.y), int(player.w), int(player.h)):
        showWin = True
        changeLevel(0)
        initiated = False

def draw2():
    engine.draw_tile(15,560,100,16)
    #if showWin:
        #engine.print("./asset/font/text.ttf", "Win!", 300, 60, 24)

