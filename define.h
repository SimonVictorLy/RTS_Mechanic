#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include <stdlib.h> // abs

#include "mystructs.h"
#include "collisions.h"
#include "LTexture.h"
#include <queue>
#include "Tile.h"
#include "unit.h"
#include "selection.h"

// Global values
const int TOTAL_TEXTURES = 4; // Textures
const int TOTAL_TRACKS = 1;   // Song tracks
const int TOTAL_SOUNDS = 1;   // Sound effects

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 800;

const int TILE_HEIGHT = 50;
const int TILE_WIDTH = 50;

const int MENU_WIDTH = 200;
const int MENU_HEIGHT = 200;

const int TOTAL_TILE_HEIGHT = SCREEN_HEIGHT/TILE_HEIGHT;
const int TOTAL_TILE_WIDTH = SCREEN_WIDTH/TILE_WIDTH;
const int TOTAL_TILE_SPRITES = 2;

enum StateTypes{
  MAIN_MENU = 0,
  INITIALIZE = 1,
  PLAYING = 2,
  GAME_OVER =3
};

enum TextureTypes{
  TEXTURE_A = 0,
  TEXTURE_B = 1,
  TEXTURE_C = 2,
  TEXTURE_D = 3
};

enum TileTypes{
  TILE_ALPHA = 0,
  TILE_BLACK = 1
};


// Main functions
bool init();
bool loadMedia();
void close();
