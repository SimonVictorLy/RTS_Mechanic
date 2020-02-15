#include "define.h"


selection::selection(SDL_Renderer* gRenderer, LTexture *texture){
  mBox.x = 0;
  mBox.y = 0;
  mBox.w = 1;
  mBox.h = 1;
  
  leftButton = false;
  mTexture = texture;
  renderer = gRenderer;
}

void selection::handleEvents(SDL_Event& e,unit *gUnits[]){
  // handle mouse inputs
  // left button down to select
  // mouse location
  // right button to set destination
  int x,y;
  SDL_GetMouseState(&x,&y); // sets destination
  
  if(!leftButton){
    mBox.x = x;
    mBox.y = y;
    mBox.w = 1;
    mBox.h = 1;
  }
  else{
    mBox.w = x - mBox.x;
    mBox.h = y - mBox.y;
  }

  
  if(e.type == SDL_MOUSEBUTTONDOWN){
    switch(e.button.button){
      case SDL_BUTTON_LEFT:
        //printf("LEFT BUTTON PRESSED!\n"); 
        leftButton = true;
        break;
      case SDL_BUTTON_RIGHT:
        moveSelected();
        break;
    }
  }
  else if(e.type == SDL_MOUSEBUTTONUP){
    switch(e.button.button){
      case SDL_BUTTON_LEFT:

       // printf("LEFT BUTTON RELEASED!\n");
        // might not work for all cases
        
        select(gUnits);
        leftButton = false;
        break;
    }
  }
}

void selection::render(SDL_Rect& camera, bool center){
  if(leftButton){
    // draw rectangle
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 125);
    SDL_RenderDrawRect(renderer, &mBox);
  }
  else{
    // do not draw rectangle
  }
  //SDL_RenderDrawRect(renderer,mBox);
}

void selection::moveSelected(){
  for(unit *i : selected){
    i->setDestination(mBox.x,mBox.y);
  }
}

void selection::select(unit *gUnits[]){
  selected.clear();

  // mouse is dragged leftwards
  if(mBox.w <0){
    mBox.x += mBox.w;
    mBox.w = -mBox.w;
  }
  // mouse is dragged upwards
  if(mBox.h <0){
    mBox.y += mBox.h;
    mBox.h = -mBox.h;
  }

  for(int i = 0; i < 5; i++){
    if(collisions::checkCollision(gUnits[i]->mCircle,mBox)){
      printf("ADDED SELECTED UNIT %d: ",i);
      printf("Circle: x=%d y=%d r=%d\n",gUnits[i]->mCircle.x,gUnits[i]->mCircle.y,gUnits[i]->mCircle.r);
      printf("Selection: x=%d, y=%d\n",mBox.x,mBox.y);
      selected.push_back(gUnits[i]);
    }
  }
}

int selection::getX(){
  return mBox.x;
}

int selection::getY(){
  return mBox.y;
}

