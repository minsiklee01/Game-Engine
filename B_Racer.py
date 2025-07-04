import engine
import time
import math
import random

#By Brickson Cain
#This game will make use of the 2.5d rendering system in DBEngine to display a racetrack in front of the player.
#main gameplay track by SoundUniverseStudio

screen = 0
depthtest = 0
gasPedal = 0
playerLane = 400
enemyOnePedal = 0.75
enemyTwoPedal = 0.5
enemyThreePedal = 0.625
enemyOneLane = 200
enemyOneDepth = 4800
enemyTwoLane = 600
enemyTwoDepth = 2400
enemyThreeLane = 400
enemyThreeDepth = 3600
score = 0
playing = False
#engine.audio.loadMusic("./asset/audio/racing.wav")

def init():
    engine.audio.loadMusic("./asset/audio/racing.wav")

def update():
    global depthtest
    global gasPedal
    global playerLane
    global enemyOneLane
    global enemyOneDepth
    global enemyTwoLane
    global enemyTwoDepth
    global enemyThreeLane
    global enemyThreeDepth
    global enemyOnePedal
    global enemyTwoPedal
    global enemyThreePedal
    global screen
    global score
    global playing

    if screen == 0:
        #update player position
        if engine.keyboard.isKeyPressed("up"):
            if gasPedal < 2:
                gasPedal = gasPedal + 0.0002
            depthtest = depthtest - gasPedal
        else:
            gasPedal = gasPedal - 0.0002
            if gasPedal < 0:
                gasPedal = 0
            depthtest = depthtest - gasPedal
        if engine.keyboard.isKeyPressed("down"):
            depthtest = depthtest + 0.1
        if engine.keyboard.isKeyPressed("left") and gasPedal > 0:
            if playerLane > 85:
                playerLane = playerLane - (0.1 * gasPedal)
        if engine.keyboard.isKeyPressed("right") and gasPedal > 0:
            if playerLane < 715:
                playerLane = playerLane + (0.1 * gasPedal)
        
        #update enemy positions
        if enemyOneDepth > 0:
            enemyOneDepth = enemyOneDepth - gasPedal + enemyOnePedal
        else:
            enemyOneDepth = 4800
            score = score + 1
            enemyOneLane = random.randint(85, 715)
        if enemyOneDepth > 4800:
            enemyOneDepth = 4800

        #update enemy two positions
        if enemyTwoDepth > 0:
            enemyTwoDepth = enemyTwoDepth - gasPedal + enemyTwoPedal
        else:
            enemyTwoDepth = 4800
            score = score + 1
            enemyTwoLane = random.randint(85, 715)
        if enemyTwoDepth > 4800:
            enemyTwoDepth = 4800

        #update enemy three positions
        if enemyThreeDepth > 0:
            enemyThreeDepth = enemyThreeDepth - gasPedal + enemyThreePedal
        else:
            enemyThreeDepth = 4800
            score = score + 1
            enemyThreeLane = random.randint(85, 715)
        if enemyThreeDepth > 4800:
            enemyThreeDepth = 4800

        if playing == False:
            engine.audio.playMusic()
            playing = True
        
        #check for collisions
        if (playerLane - 50) < (enemyOneLane + 50) and (playerLane + 50) > (enemyOneLane - 50)  and enemyOneDepth <= 100:
            screen = 1
        if (playerLane - 50) < (enemyTwoLane + 50) and (playerLane + 50) > (enemyTwoLane - 50) and enemyTwoDepth <= 100:
            screen = 1
        if (playerLane - 50) < (enemyThreeLane + 50) and (playerLane + 50) > (enemyThreeLane - 50) and enemyThreeDepth <= 100:
            screen = 1
        
        
    elif screen == 1:
        #print(score)
        if playing == True:
            engine.audio.stopMusic()
            playing = False
        if engine.keyboard.isKeyPressed("enter"):
            screen = 0
            depthtest = 0
            gasPedal = 0
            playerLane = 400
            enemyOnePedal = 0.75
            enemyTwoPedal = 0.5
            enemyThreePedal = 0.625
            enemyOneLane = 200
            enemyOneDepth = 4800
            enemyTwoLane = 600
            enemyTwoDepth = 2400
            enemyThreeLane = 400
            enemyThreeDepth = 3600
            score = 0
    

def draw():
    global depthtest
    global playerLane
    global enemyOneLane
    global enemyOneDepth
    global enemyTwoLane
    global enemyTwoDepth
    global enemyThreeLane
    global enemyThreeDepth
    global score

    #render track
    engine.draw_line(0, 600, 0, 0, 0, 4800, 0, 255, 0)
    engine.draw_line(800, 600, 0, 0, 0, 4800, 0, 255, 0)
    roadline0 = int(depthtest % 4800)
    roadline1 = roadline0 - 480
    if roadline1 < 0:
        roadline1 = 0
    if roadline1 > 4800:
        roadline1 = 4800
    engine.draw_line(400, 600, roadline0, 400, 600, roadline1, 255, 255, 0)
    
    roadline2 = int((depthtest - 960) % 4800)
    roadline3 = roadline2 - 480
    if roadline3 < 0:
        roadline3 = 0
    if roadline3 > 4800:
        roadline3 = 4800
    engine.draw_line(400, 600, roadline2, 400, 600, roadline3, 255, 255, 0)
    
    roadline4 = int((depthtest - 1920) % 4800)
    roadline5 = roadline4 - 480
    if roadline5 < 0:
        roadline5 = 0
    if roadline5 > 4800:
        roadline5 = 4800
    engine.draw_line(400, 600, roadline4, 400, 600, roadline5, 255, 255, 0)

    roadline6 = int((depthtest - 2880) % 4800)
    roadline7 = roadline6 - 480
    if roadline7 < 0:
        roadline7 = 0
    if roadline7 > 4800:
        roadline7 = 4800
    engine.draw_line(400, 600, roadline6, 400, 600, roadline7, 255, 255, 0)

    roadline8 = int((depthtest - 3840) % 4800)
    roadline9 = roadline8 - 480
    if roadline9 < 0:
        roadline9 = 0
    if roadline9 > 4800:
        roadline9 = 4800
    engine.draw_line(400, 600, roadline8, 400, 600, roadline9, 255, 255, 0)

    #render enemies
    engine.draw_rect(int(enemyOneLane - 50), 550, int(enemyOneDepth-1), 100, 50, 0, 0, 255, 255)
    engine.draw_circle(int(enemyOneLane - 15), 535, int(enemyOneDepth), 16, 255, 255, 255, 255)
    engine.draw_rect(int(enemyOneLane - 85), int(570-(depthtest % 4)), int(enemyOneDepth-2), 35, 35, 128, 128, 128, 255)
    engine.draw_rect(int(enemyOneLane + 50), int(570-(depthtest % 4)), int(enemyOneDepth-2), 35, 35, 128, 128, 128, 255)

    engine.draw_rect(int(enemyTwoLane - 50), 550, int(enemyTwoDepth-1), 100, 50, 0, 255, 0, 255)
    engine.draw_circle(int(enemyTwoLane - 15), 535, int(enemyTwoDepth), 16, 255, 255, 255, 255)
    engine.draw_rect(int(enemyTwoLane - 85), int(570-(depthtest % 4)), int(enemyTwoDepth-2), 35, 35, 128, 128, 128, 255)
    engine.draw_rect(int(enemyTwoLane + 50), int(570-(depthtest % 4)), int(enemyTwoDepth-2), 35, 35, 128, 128, 128, 255)

    engine.draw_rect(int(enemyThreeLane - 50), 550, int(enemyThreeDepth-1), 100, 50, 255, 255, 0, 255)
    engine.draw_circle(int(enemyThreeLane - 15), 535, int(enemyThreeDepth), 16, 255, 255, 255, 255)
    engine.draw_rect(int(enemyThreeLane - 85), int(570-(depthtest % 4)), int(enemyThreeDepth-2), 35, 35, 128, 128, 128, 255)
    engine.draw_rect(int(enemyThreeLane + 50), int(570-(depthtest % 4)), int(enemyThreeDepth-2), 35, 35, 128, 128, 128, 255)

    #render car
    engine.draw_rect(int(playerLane - 50), 550, 61, 100, 50, 255, 0, 0, 255)
    engine.draw_circle(int(playerLane - 15), 535, 62, 16, 255, 255, 255, 255)
    engine.draw_rect(int(playerLane - 85), int(570-(depthtest % 4)), 60, 35, 35, 128, 128, 128, 255)
    engine.draw_rect(int(playerLane + 50), int(570-(depthtest % 4)), 60, 35, 35, 128, 128, 128, 255)

    #render score
    if screen == 0:
        engine.print("./asset/font/EightBitDragon-anqx.ttf",str(score), 50, 50, 24)
        engine.print("./asset/font/EightBitDragon-anqx.ttf","Use the arrow keys to drive", 50, 100, 24)
    elif screen == 1:
        if score > 0:    
            engine.print("./asset/font/EightBitDragon-anqx.ttf",str(score), int(400 - (math.floor(math.log10(score)) + 1) * 24), 50, 96)
        else:
            engine.print("./asset/font/EightBitDragon-anqx.ttf","You kinda suck at this", 100, 100, 48)
        engine.print("./asset/font/EightBitDragon-anqx.ttf","Press Enter to restart", 50, 200, 48)
