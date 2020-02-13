#include "define.h"

unit::unit(LTexture *inTexture){
  mBox.x = 0;
  mBox.y = 0;
  mBox.w = UNIT_WIDTH;
  mBox.h = UNIT_HEIGHT;  
  texture = inTexture;

  destX = mBox.x;
  destY = mBox.y;
}


void unit::setDestination(double x, double y){
  destX = x - mBox.w/2.0;
  destY = y - mBox.h/2.0;
}

void unit::handleEvents(SDL_Event &e){
}

void unit::move(){
  // a-star
  // will have to interact with tilemap
  
  if(destX != mBox.x || destY!=mBox.y){
    
    double mVelx, mVely;
    double dx, dy, dm;

    dx = destX - mBox.x;
    dy = destY - mBox.y;
    
    dm = std::sqrt(dx*dx+dy*dy);
   
    mVelx = mVel*(dx/dm);
    mVely = mVel*(dy/dm);
    
    // int += float
    mBox.x += mVelx;
    if(std::abs(dx) < mVel){
      mBox.x = destX;
    }

    mBox.y += mVely;
    if(std::abs(dy) < mVel){
      mBox.y = destY;
    }

  }
}

void unit::render(SDL_Rect &camera){
  texture->render(mBox.x-camera.x, mBox.y-camera.y); 
}

int unit::getX(){
  return mBox.x;
}

int unit::getY(){
  return mBox.y;
}
