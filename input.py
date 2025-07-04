import engine

def init():
    print(engine.joystick.isConnected(0))


def update():
    print(engine.keyboard.isKeyPressed("h"))
    print(engine.joystick.isButtonPressed(0,0))
    print(engine.joystick.getAxisPosition(0,"x"))

def draw():
  print("")

