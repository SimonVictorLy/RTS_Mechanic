#include "define.h"

Tile::Tile(int x, int y, int tileType, LTexture *textureMap, SDL_Rect *typeSelect){
  mBox.x = x;
  mBox.y = y;

  mBox.w = TILE_WIDTH;
  mBox.h = TILE_HEIGHT;

  mTexture = textureMap;
  mType = tileType;
  mClip = typeSelect;
}

void Tile::render(SDL_Rect& camera)
{
  if(collisions::checkCollision(camera, mBox)){
    //printf("%d,%d\t",mBox.x-camera.x,mBox.y-camera.y);
    //printf("%d,%d,%d,%d\n",mClip->x,mClip->y,mClip->w,mClip->h);
    mTexture->render(mBox.x - camera.x, mBox.y - camera.y, mClip);
  }
}

int Tile::getType(){
  return mType;
}

SDL_Rect Tile::getBox()
{
  return mBox;
}


