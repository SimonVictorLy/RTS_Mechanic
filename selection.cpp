#include "define.h"


selection::selection(SDL_Renderer* gRenderer, LTexture *texture){
  mBox.x = 0;
  mBox.y = 0;
  mBox.w = 1;
  mBox.h = 1;
  
  rightButton = false;
  mTexture = texture;
  renderer = gRenderer;
}

void selection::handleEvents(SDL_Event& e,unit *gUnits[]){
  // handle mouse inputs
  // left button down to select
  // mouse location
  // right button to set destination
  if(e.type == SDL_MOUSEBUTTONDOWN){
    int x,y;
    SDL_GetMouseState(&x,&y); // sets destination
    mBox.x = x;
    mBox.y = y;
    switch(e.button.button){
      case SDL_BUTTON_LEFT:
        select(gUnits);
        break;
      case SDL_BUTTON_RIGHT:
        moveSelected();
        break;
    }
  }
}

void selection::render(SDL_Rect& camera, bool center){
  //SDL_RenderDrawRect(renderer,mBox);
}

void selection::moveSelected(){
  for(unit *i : selected){
    i->setDestination(mBox.x,mBox.y);
  }
}


bool selection::CC(SDL_Rect &a, SDL_Rect &b){
  int leftA, leftB;
  int rightA, rightB;
  int topA, topB;
  int bottomA, bottomB;

  leftA = a.x;
  rightA = a.x + a.w;
  topA = a.y;
  bottomA = a.y + a.h;

  leftB = b.x;
  rightB = b.x + b.w;
  topB = b.y;
  bottomB = b.y + b.h;

  // Check extreme of one side of A exceeds the opposite in B
  if(bottomA <= topB) return false;
  if(topA >= bottomB) return false;
  if(rightA <= leftB) return false;
  if(leftA >= rightB) return false;

  return true;
}

void selection::select(unit *gUnits[]){
  selected.clear();
  for(int i = 0; i < 5; i++){
    if(CC(mBox,gUnits[i]->mBox)){
      printf("ADDED SELECTED UNIT %d\n",i);
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

