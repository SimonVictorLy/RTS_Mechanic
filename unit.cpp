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

bool unit::isValid(int row, int col, int ROW, int COL) { 
    // Returns true if row number and column number is in range 
    return (row >= 0) && (row < ROW) && (col >= 0) && (col < COL); 
} 

bool unit::isUnBlocked(Tile** tiles, int row, int col, int ROW) { 
    // Returns true if the cell is not blocked else false 
    return (tiles[row+col*ROW]->getType() > 0);
} 

bool unit::isDestination(int row, int col, Pair dest){ 
    return (row == dest.first && col == dest.second);
}

// A Utility Function to calculate the 'h' heuristics. 
double calculateHValue(int row, int col, Pair dest) { 
    // Return using the distance formula Euclidean Distance for cost 
    return ((double)sqrt ((row-dest.first)*(row-dest.first)+
          (col-dest.second)*(col-dest.second))); 
} 
  
// A Utility Function to trace the path from the source 
// to destination 
void tracePath(cell **cellDetails, Pair dest) {

    printf ("\nThe Path is "); 
    int row = dest.first; 
    int col = dest.second; 
  
    std::stack<Pair> Path; 
  
    while (!(cellDetails[row][col].parent_i == row 
             && cellDetails[row][col].parent_j == col )){ 
        Path.push (Pair{row, col}); 
        int temp_row = cellDetails[row][col].parent_i; 
        int temp_col = cellDetails[row][col].parent_j; 
        row = temp_row; 
        col = temp_col; 
    } 
  
    Path.push (Pair{row, col}); 
    while (!Path.empty()){ 
        Pair p = Path.top(); 
        Path.pop(); 
        printf("-> (%d,%d) ",p.first,p.second); 
    } 
  
    return; 
}

void unit::aStarSearch(Tile **tiles,  Pair start, Pair destEnd, int ROW, int COL){


}

void unit::setDestination(double x, double y, Tile** tiles, int mapX, int mapY){

  // empty previous entries  
  std::queue<Pair>empty;
  std::swap(dest,empty);  

  int tileWidth = tiles[0]->getBox().w;

  Pair start = {mCircle.x/tileWidth, mCircle.y/tileWidth};
  Pair destEnd = {x/tileWidth,y/tileWidth};

  if(tiles[destEnd.first+destEnd.second*mapX]->getType()>0) return;

  printf("%d,%d -> %d,%d\n",start.first,start.second,destEnd.first,destEnd.second);
  
  // A* algorithm
  aStarSearch(tiles,start,destEnd, mapX,mapY);

  dest.push(Pair{tileWidth*destEnd.first+mCircle.r,tileWidth*destEnd.second+mCircle.r});
  destX = dest.front().first;
  destY = dest.front().second;
}

void unit::handleEvents(SDL_Event &e){
}

bool unit::unitCollides(unit *gUnits[]){
  bool collides = false;
  for(int i = 0;i<5;i++){
    if(gUnits[i]->id != id && 
        collisions::checkCollision(gUnits[i]->mCircle,mCircle)){ 
      
      float angle;
      int dX,dY,dif;
      dX = gUnits[i]->mCircle.x - mCircle.x;
      dY = gUnits[i]->mCircle.y - mCircle.y;

      angle = dX!=0? atan(dY/dX) : 0;
      dif = mCircle.r + gUnits[i]->mCircle.r - std::ceil(std::sqrt(dX*dX + dY*dY));
      
      if(dX<0){ 
        // unit approaches from the right
        mCircle.x += dif*cos(angle);
        mCircle.y += dif*sin(angle);
      }else{
        // unit approaches from the left
        mCircle.x -= dif*cos(angle);
        mCircle.y -= dif*sin(angle);
      }

      collides = true;
    }
  } 
  return collides;
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
  
  if(!dest.empty()){
    
    int mVelx, mVely;
    double dx, dy, dm;

    dx = destX - mCircle.x;
    dy = destY - mCircle.y;
    
    dm = std::sqrt(dx*dx+dy*dy);
   
    mVelx = mVel*(dx/dm);
    mVely = mVel*(dy/dm);
    
    mCircle.x += mVelx;
    if(wallCollides(tiles,tileCount)){
      mCircle.x -= mVelx;
    }
    else if(std::abs(dx) < mVel){
      mCircle.x = destX;
    }

    mCircle.y += mVely;   
    if(wallCollides(tiles,tileCount)){
      mCircle.y -= mVely;
    }
    else if(std::abs(dy) < mVel){
      mCircle.y = destY;
    }

    if( mCircle.x == destX && mCircle.y == destY){
      printf("Remove Node {%d,%d}\n",destX,destY);
      dest.pop();
      destX = dest.front().first;
      destY = dest.front().second;
    }
  }
  unitCollides(gUnits); 

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
