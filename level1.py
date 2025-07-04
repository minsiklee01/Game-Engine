import engine
from game import player, changeLevel

gotKey = False
initiated = False

def init1():
    global initiated, gotKey
    gotKey = False

    engine.load_tilemap("asset/map/map1.json", "asset/sprite/map/spritesheet.png", 30, 30)
    engine.add_area2d("goal", 560, 140, 16, 16)
    engine.add_area2d("key",560, 100, 16, 16)
    player.x = 64
    player.y = 64
    initiated = True
    

def update1():
    global gotKey, initiated

    if not initiated:
        init1()

    if engine.is_in_area("key", int(player.x), int(player.y), int(player.w), int(player.h)):
        gotKey = True

    if engine.is_in_area("goal", int(player.x), int(player.y), int(player.w), int(player.h)):
        changeLevel(2) 
        player.x = 64
        player.y = 64
        initiated = False

def draw1():
    if not gotKey:
        engine.draw_tile(15,560,100,16)
