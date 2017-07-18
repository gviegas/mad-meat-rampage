# Editing

The files under [data](../data) are used to configure the game parameters. It allows you to create/modify levels, replace
textures, set animations and play with character attributes.

Note: you can easily break the game while messing with this files so... go wild!

### Levels

The file [game.setup](../data/game.setup) holds a list of levels to be loaded in the game. Each level is defined by
a [map](../data/maps) file and an [entity](../data/entities) file. A single level in game.setup`is specified as follows:

`LEVEL mapX.map entityX.ent`

Where *mapX.map* is the path of your map file and *entityX.ent* is the path of your entity file.

A map file is nothing more than a set of coordinates to indicate where a given tile should be placed. It has the following format:

`TILE type x y`

*type* is a number that maps to a tile texture. *x* and *y* are the coordinates to place the tile in the map. SInce the game uses a
fixed dimesnion of 1280x960 and each tile is 64x64, accepted coordinates vary from 0 0 (top left) to 19 14 (bottom right). 
Take a look at the [map1.map](../data/maps/map1.map) to see how it's done.

An entity file describes everything (except tiles) that should go in a map. This file structure does not have a single format, it
depends of the entity you want to add. See [entities1.ent](../data/entities/entities1.ent) for a reference.

### Textures and Animations

All the game textures used in the game can be found in [data/textures/](../data/textures/). Textures that will be affected by gravity must have
64x64 pixels. Animation files are defined as follows:

`ANIMATION action x y w h frames`

*action* is which action should trigger the given animation. Example of actions are *Jump-Left* and *Die* (you can check other
actions [here](../data/animations/chicken.anim).

*x* and *y* are offsets, in pixels, from the top left of the sprite sheet. The dimesion of each sprite is given by *w* and *h*,
while *frames* is how many frames there is for this animation. Note that all frames of the same animation MUST be placed side 
by side in the sprite sheet.

### Characters and Objects

Characters and objects files are located in [data/confs](../data/confs). This conf files are used to set the texture file, 
the animation file and other parameters specific of the given character/object. For example, the Pig character is defined in
[pig.conf](../data/confs/pig.conf) as follows:

```
TEXTURE data/textures/pig.png
BBOX  0 0 64 64
SPEED 8.0 0
IMPULSE 350.0
ANIMATION data/animations/pig.anim
```
The TEXTURE line contains the path of the pig sprite sheet, and the ANIMATION line contains the path to the animation file. 
BBOX is the bounding box of the pig, used for collision detection (you probably shouldn't mess with it though, the collision
algorithm isn't that great and may not like that). You can play with the SPEED and IMPULSE attributes to tweak the pig as 
you wish. Take a look at the other conf files to find out what else you can do.

