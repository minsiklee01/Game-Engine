import engine
from game import changeLevel
keys = engine.keyboard

options = ["play", "exit"]
selected = 0

prev_up = False
prev_down = False

def update0():
  global selected, prev_up, prev_down
  is_up = keys.isKeyPressed("up")
  is_down = keys.isKeyPressed("down")

  if is_up and not prev_up:
    selected = 1 - selected
  elif is_down and not prev_down:
    selected = 1 - selected

  prev_up = is_up
  prev_down = is_down

  if keys.isKeyPressed("space") or keys.isKeyPressed("enter"):
      if selected == 0:
        changeLevel(1)
      else:
        engine.close()
  

def draw0():
  global options

  engine.rectangle.setFillColor(25,25,25)
  engine.rectangle.draw(0,0,1000,1000)

  for i in range(len(options)):
    if i == selected:
      engine.textColor(255,0,0)
    else:
      engine.textColor(255,255,255)
    engine.print("./asset/font/text.ttf", options[i], 330, 150 + 100*i, 50)