# DBM Game Engine

## Members
This engine was made by David Lee and Brickson Cain.

## Notable Features
We designed the engine with the main goals being the simulation of 3d in a 2d engine, and joypad input.  We thought that these would be fun to apply to different genres, with David wanting to make a platformer and Brickson wanting to make a Pole Position-style racing game.

## Current State
The engine can draw circles, squares and lines, all taking their typical 2-dimensional inputs as well as depth inputs.  As the depth value gets larger, the object is drawn smaller and smaller, and is positioned closer and closer to the center of the screen, mimicing a one-point perspective drawing.  B_Racer (by Brickson Cain) currently demonstrates these features of the engine by drawing a background that mimics a road with lines moving toward the camera and a simple car, making it seem like the camera is following a car as it drives down the tunnel.  There are now opponent cars as well, which move towards the horizon at different speeds depending on the speed of the player's car.

The engine supports input from keyboard and joystick. Keyboard can detect keys. Joystick can detect if a joystick is connected, if a button is pressed, and what the current axis position is.

Key 2D platformer features such as importing tile map, sprite sheet, animation, collision, detect area enter and text pringing is supported.

## Documentation
### Engine  

>```draw_circle(long x, long y, lons z, long r, long R, long G, long B, long A)```  
Draw a circle centered at (x,y) at depth z with radius r in the window.  It will have a color with RGB value, and its transparency will be decided by A.  
**Parameters**  
`long` x position  
`long` y position  
`long` z depth  
`long` r radius  
`long` R red  
`long` G green  
`long` B blue  
`long` A alpha  
**Returns**  
Nothing  

>```draw_rect(long x, long y, lons z, long w, long h, long R, long G, long B, long A)```  
Draw a rectangle centered at (x,y) at depth z with width w and height h in the window.  It will have a color with RGB value, and its transparency will be decided by A.  
**Parameters**  
`long` x position  
`long` y position  
`long` z depth  
`long` w width
`long` h height  
`long` R red  
`long` G green  
`long` B blue  
`long` A alpha    
**Returns**  
Nothing  

>```draw_line(long x1, long y1, lons z1, long x2, long y2, long z2, long R, long G, long B)```  
Draw a line from (x1,y1,z1) to (x2,y2,z2) in the window.  It will have a color with RGB value.  
**Parameters**  
`long` x1 position  
`long` y1 position  
`long` z1 position  
`long` x2 position  
`long` y2 position  
`long` z2 position  
`long` R red  
`long` G green  
`long` B blue  
**Returns**  
Nothing  

>```print(string font, string string, int x, int y, int size)```  
Print text at (`x`, `y`)  
**Parameters**  
`font` path to the font file  
`string` string to print   
`x` x coordinate to print  
`y` y coordinate to print  
`size` size of the text  
**Returns**  
Nothing  

>```load_tilemap(string filename, string spriteName, int offsetX, int offsetY)```  
Import [tilemap](#tilemap) json file and spritesheet image from the path `filenam` and `spriteName` respectively. Apply offset of `offsetX` and `offsetY`.  
**Parameters**  
`filename` path to the tilemap json file  
`spriteName` path to the sprite sheet image file  
`offsetX` offset x  
`offsetY` offset y  
**Returns**  
Nothing  

>```draw_map()```  
Draw loaded map and spritesheet.  
**Parameters**  
None   
**Returns**  
Nothing  

>```is_colliding(int x, int y, int w, int h)```  
Check if the `w` width, `h` height rectangular area with (`x`,`y`) top-left collides with any collidable tile of the map.  
**Parameters**  
`x` top left x coordinate of the rectangular area to check (e.g, player.x)    
`y` top left y coordinate of the rectangular area to check (e.g, player.y)   
`w` width of the rectangular area to check (e.g, player.w)  
`h` heigh of the rectangular area to check (e.g, player.h)   
**Returns**  
Nothing  

>```add_area2d(string name, int x, int y, int w, int h)```  
Create a 2D area with the given name. It is created to call `is_in_area()`
**Parameters**  
`name` Name of the area  
`x` top left x coordinate of the rectangular area  
`y` top left y coordinate of the rectangular area  
`w` width of the area  
`h` heigh of the area   
**Returns**  
Nothing  

>```is_in_area(string name, int x, int y, int w, int h)```  
Return `true` if the rectangle that has `x` and `y` as the top-left and `w`width `h`height is in the `name`2d area.   
**Parameters**  
`name` Name of the area to check  
`x` top left x coordinate of the rectangle area to check. (e.g, player.x)  
`y` top left y coordinate of the rectangle area to check. (e.g, player.y)  
`w` width of the area to check (e.g, player.h)  
`h` heigh of the area to check (e.g, player.x)   
**Returns**  
`True` if is area, `False` if not.  

>```draw_tile(int tile_id, int x, int y, int tileSize)```  
Draw a tile with index number of `tile_id` from the loaded sprite sheet at (`x`,`y`). This tile must have width and height of `tileSize`.    
**Parameters**  
`tile_id` Index number of the tile to draw  
`x` x coordinate to draw at  
`y` y coordinate to draw at  
`tileSize` width and height of the tile   
**Returns**  
Nothing. 

>```draw_sprite_frame(string filename, string frame_index, int x, int y, int frame_w, int frame_h, int scale, int faceRight)```  
Draw a sprite with index number of `frame_index` from spritesheet `filename` at (`x`, `y`). The sprite must have width of `frame_w` and height of `frame_h`. The sprite is scaled by `scale` times and flips vertically if `faceRight` is `False`.    
**Parameters**  
`filename` Path of the spritesheet to use  
`frame_index` index number of the sprite to draw  
`x` x coordinate to draw at (E.g, player.x)  
`y` y coordinate to draw at (E.g, player.y)  
`frame_w` width of the sprite  
`frame_h` height of the sprite  
`scale` sprite is drawn this times bigger  
`faceRight` flips if false  
**Returns**  
Nothing. 

### tilemap
Tilemap is a json file that contains the information of the map with following structure:
```
{
  "tileSize": 16,
  "mapWidth": 38,
  "mapHeight": 14,
  "layers": [
    {
      "name": "Background",
      "tiles": [
        {
          "id": "26",
          "x": 0,
          "y": 6
        },
      ],
      "collider": false
    },
    {
     // more layers
    }
  ]
}
```

### Engine.keyboard  

>```isKeyPressed(string)```  
Check if a key is pressed.  
**Parameters**  
`string` [key](#keys) to check  
**Returns**  
  true if the key is pressed, false otherwise    

#### Keys  
| Key         | Description                                |
|-------------|--------------------------------------------|
| `unknown`   | Unhandled key.                             |
| `a` ~ `z`   | The lowercase alphabet keys.               |
| `num0` ~ `num9` | Number keys at the top of the keyboard.   |
| `escape`    | Escape key.                                |
| `lcontrol`  | Left Control key.                          |
| `lshift`    | Left Shift key.                            |
| `lalt`      | Left Alt key.                              |
| `lsystem`   | Left system key (e.g., Windows key).       |
| `rcontrol`  | Right Control key.                         |
| `rshift`    | Right Shift key.                           |
| `ralt`      | Right Alt key.                             |
| `rsystem`   | Right system key.                          |
| `menu`      | Menu key.                                  |
| `lbracket`  | Left square bracket `[`.                   |
| `rbracket`  | Right square bracket `]`.                  |
| `semicolon` | Semicolon `;`.                             |
| `comma`     | Comma `,`.                                 |
| `period`    | Period `.`.                                |
| `quote`     | Quote `'`.                                 |
| `slash`     | Slash `/`.                                 |
| `backslash` | Backslash `\`.                             |
| `tilde`     | Tilde `~`.                                 |
| `equal`     | Equal sign `=`.                            |
| `hyphen`    | Hyphen `-`.                                |
| `space`     | Space bar.                                 |
| `enter`     | Enter/Return key.                          |
| `backspace` | Backspace key.                             |
| `tab`       | Tab key.                                   |
| `pageup`    | Page Up key.                               |
| `pagedown`  | Page Down key.                             |
| `end`       | End key.                                   |
| `home`      | Home key.                                  |
| `insert`    | Insert key.                                |
| `delete`    | Delete key.                                |
| `add`       | Numpad `+`.                                |
| `subtract`  | Numpad `-`.                                |
| `multiply`  | Numpad `*`.                                |
| `divide`    | Numpad `/`.                                |
| `left`      | Left arrow key.                            |
| `right`     | Right arrow key.                           |
| `up`        | Up arrow key.                              |
| `down`      | Down arrow key.                            |
| `numpad0` ~ `numpad9` | Number pad keys 0–9.             |
| `f1` ~ `f15`| Function keys F1 to F15.                   |
| `pause`     | Pause/Break key.                           |
  

### Engine.joystick  

>```isConnected(int)```  
Return if joystick is connected  
**Parameters**  
`int` Index of the joystick to check  
**Returns**  
true if the joystick is connected, false otherwise  
  
>```isButtonPressed(int, int)```  
Check if a joystick button is pressed.  
If the joystick is not connected, this function returns false.  
**Parameters**  
`int`	Index of the joystick  
`int`	Button to check  
**Returns**  
true if the button is pressed, false otherwise  
  
>```getAxisPosition(int, int)```  
Get the current position of a joystick axis.  
If the joystick is not connected, this function returns 0.  
**Parameters**  
`int`	Index of the joystick  
`int`	Axis to check  
**Returns**  
  urrent position of the axis, in range [-100 .. 100]
