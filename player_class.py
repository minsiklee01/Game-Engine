import engine
from enum import Enum
from game import changeLevel

keys = engine.keyboard

FRAME_COUNTS = {
    "idle": 8,
    "run": 7,
    "jump": 13
}

class characterState(Enum):
    IDLE = 0
    RUN = 1
    JUMP = 2

animationSprite = {
    0: "./asset/sprite/character/Idle.png",
    1: "./asset/sprite/character/Run.png",
    2: "./asset/sprite/character/Jump.png"
}

def check_collision(x, y, w, h):
    colliding = engine.is_colliding(int(x), int(y), int(w), int(h))
    return colliding

class Player:
    def __init__(self):
        self.x = 64
        self.y = 64
        self.w = 16
        self.h = 16
        self.vx = 0
        self.vy = 0
        self.faceRight = True
        self.on_ground = False
        self.state = characterState.IDLE
        self.frame = 0
        self.frame_timer = 0.0
        self.frame_delay = 0.1

    def update(self, dt):
        speed = 100
        gravity = 300
        jump_velocity = -150 
        justJumped = False
        
        # horizontal movement
        self.vx = 0
        if keys.isKeyPressed("left"):
            self.vx = -speed
            self.state = characterState.RUN
            self.faceRight = False
        elif keys.isKeyPressed("right"):
            self.vx = speed
            self.state = characterState.RUN
            self.faceRight = True

        # jump
        if keys.isKeyPressed("space") and self.on_ground:
            justJumped = True
            self.vy = jump_velocity
            self.state = characterState.JUMP
            self.frame = 0
            self.on_ground = False

        # apply gravity
        self.vy += gravity * dt

        # attempt horizontal move
        new_x = self.x + self.vx * dt
        if not check_collision(new_x, self.y, self.w, self.h):
            self.x = new_x

        # attempt vertical move
        new_y = self.y + self.vy * dt
        if not check_collision(self.x, new_y, self.w, self.h):
            self.y = new_y
            self.on_ground = False
        else:
            self.vy = 0
            self.on_ground = True
            if justJumped:
                self.state = characterState.IDLE
                self.frame = 0
                justJumped = False

        # update animation 
        if self.vx == 0 and self.on_ground:
            self.state = characterState.IDLE
        self.update_animation(dt)

        if self.x < 0 or self. x > 1500 or self.y > 900:
            changeLevel(0)
            self.x = 64
            self.y = 64

    def update_animation(self, dt):
        self.frame_timer += dt
        if self.frame_timer >= self.frame_delay:
            self.frame_timer = 0
            self.frame += 1
            if self.frame >= FRAME_COUNTS[self.state.name.lower()]:
                self.frame = 0
    
    def draw(self):
        engine.draw_sprite_frame(
        animationSprite[self.state.value], 
        self.frame, 
        int(self.x), 
        int(self.y), 
        128, 
        128, 
        3,
        self.faceRight
    )

