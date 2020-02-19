#include "define.h"

unit::unit(LTexture *inTexture, int unitID, int initX, int initY){
  id = unitID;
  mCircle.x = initX;  // center
  mCircle.y = initY;  // center
  mCircle.r = UNIT_WIDTH/2;

  texture = inTexture;

  destX = initX;
  destY = initY;
}


void unit::setDestination(double x, double y){
  destX = x;
  destY = y;
}

void unit::handleEvents(SDL_Event &e){
}

bool unit::unitCollides(unit *gUnits[]){
  for(int i = 0;i<5;i++){
    if(gUnits[i]->id != id && 
        collisions::checkCollision(gUnits[i]->mCircle,mCircle)) 
      return true;
  } 
  return false;
}

bool unit::wallCollides(Tile** tiles, int tileCount){
  for(int i = 0; i < tileCount ;i++){
    if(tiles[i]->getType()>0){
      SDL_Rect tile = tiles[i]->getBox();
      if(collisions::checkCollision(mCircle,tile)){
        return true;
      }
    }
  }
  return false;
}

void unit::move(unit *gUnits[],Tile **tiles, int tileCount){
  // a-star
  // will have to interact with tilemap
  
  if(destX != mCircle.x || destY!=mCircle.y){
    
    int mVelx, mVely;
    double dx, dy, dm;

    dx = destX - mCircle.x;
    dy = destY - mCircle.y;
    
    dm = std::sqrt(dx*dx+dy*dy);
   
    mVelx = mVel*(dx/dm);
    mVely = mVel*(dy/dm);
    
    // int += float
    mCircle.x += mVelx;
    if(std::abs(dx) < mVel){
      mCircle.x = destX;
    }
    if(unitCollides(gUnits) || wallCollides(tiles,tileCount)){
      mCircle.x -= mVelx;
    }
    mCircle.y += mVely;
    if(std::abs(dy) < mVel){
      mCircle.y = destY;
    }
    if(unitCollides(gUnits) || wallCollides(tiles,tileCount)){
      mCircle.y -= mVely;
    }


  }
}

void unit::render(SDL_Rect &camera){

  int renderX = mCircle.x - mCircle.r;
  int renderY = mCircle.y - mCircle.r;

  texture->render(renderX-camera.x, renderY-camera.y); 
}

int unit::getX(){
  return mCircle.x;
}

int unit::getY(){
  return mCircle.y;
}
