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

bool unit::isUnBlocked(Tile** tiles, int row, int col, int COL) { 
    // Returns true if the cell is not blocked else false 
    return (tiles[row*COL+col]->getType() == 0);
} 

bool unit::isDestination(int row, int col, Pair destEnd){ 
    return (row == destEnd.second && col == destEnd.first);
}

// A Utility Function to calculate the 'h' heuristics. 
double unit::calculateHValue(int row, int col, Pair destEnd) { 
    // Return using the distance formula Euclidean Distance for cost 
    return ((double)sqrt ( abs((row-destEnd.second) * (row-destEnd.first) + (col-destEnd.second) * (col-destEnd.second)))); 
} 
  
// A Utility Function to trace the path from the source to destination 
void unit::tracePath(cell **cellDetails,Pair start, Pair destEnd, int ROW, int COL, int tileWidth) {

    printf ("\nThe Path is "); 
    int row = destEnd.second; 
    int col = destEnd.first; 
    int index = row*COL + col;

    std::stack<Pair> Path; 
    

    // while the parent does not equal itself 
    while (!(cellDetails[index]->parent_i == row && cellDetails[index]->parent_j == col )){ 
        //printf("parent[i,j]=%d,%d\n",cellDetails[index]->parent_i,cellDetails[index]->parent_j);
        
        Path.push (Pair{row, col}); 
        int temp_row = cellDetails[index]->parent_i; 
        int temp_col = cellDetails[index]->parent_j; 
        row = temp_row; 
        col = temp_col; 
        index = row*COL +col;
    } 
  
    Path.push (Pair{row, col}); 
    while (!Path.empty()){ 
        Pair p = Path.top();
        // Pair{x,y}
        dest.push(Pair{tileWidth*p.second+mCircle.r,tileWidth*p.first+mCircle.r});
        Path.pop(); 
        //printf("-> (%d,%d) ",p.first,p.second); 
    } 
  
    return; 
}

void unit::aStarSearch(Tile **tiles, Pair start, Pair destEnd, int ROW, int COL){
  // ROW = TOTAL IN THE Y
  // COL = TOTAL IN THE X

  int tileWidth = tiles[0]->getBox().w;
  //printf("===========================================================================\n");
  //printf("Starting A* algorithm %dx%d destEnd:%d,%d start:%d,%d\n",ROW,COL,destEnd.first,destEnd.second,start.first,start.second);
  // start{x,y} start{col,row}
  if(!isValid(start.second, start.first, ROW, COL)) {printf("INVALID\n"); return;}
  if(!isValid(destEnd.second, destEnd.first, ROW, COL)) {printf("INVALID\n"); return;}
  if(!isUnBlocked(tiles, destEnd.second, destEnd.first, COL)){printf("DESTBLOCKED\n");return;}
  if(!isUnBlocked(tiles, start.second, start.first, COL)){printf("STARTBLOCKED\n");return;}
  if(isDestination(start.second, start.first, destEnd)){return;}
  // printf("Seeking path...\n");

 
  bool closedList[ROW*COL] = {false}; // list of cells that won't be explored
  cell **cellDetails = (cell**) malloc(sizeof(cell*)*ROW*COL); // structure to hold the list
 
  // printf("Intializing distance costs\n"); 
  int i,j, index;
  for(i = 0; i < ROW; i++){
    for(j = 0; j < COL; j++){
      index = i*COL+j;
      cellDetails[index] = (cell*) malloc(sizeof(cell));
      cellDetails[index]->f = FLT_MAX; // total distance cost
      cellDetails[index]->g = FLT_MAX; // distance spend start to cur (exact)
      cellDetails[index]->h = FLT_MAX; // distance cost cur to end (est.)
      cellDetails[index]->parent_i = -1;
      cellDetails[index]->parent_j = -1;
    }
  }
 
  i = start.second;   // i is the second, refering to the rows, y.
  j = start.first;    // j is the first, refering to the cols, x.
  // printf("Initialize Start[%d,%d]\n",i,j);
  
  // intialize start position 
  index = i*COL + j;
  cellDetails[index]->f = 0.0;
  cellDetails[index]->g = 0.0;
  cellDetails[index]->h = 0.0;
  cellDetails[index]->parent_i = i;
  cellDetails[index]->parent_j = j;
  
  // set to-be-evaluated list IMPORTANT THAT SET IS ORDERED BY F, THE COST
  std::set<pPair> openList; 
  openList.insert(std::make_pair(0.0,start));

  bool foundDest = false;

  // grid is in the second quadrant
  // {dx,dy} = S, N, E, W, SE, NW, SW, NE
  int offset[8][2] = {{0,1},{0,-1},{1,0},{-1,0},
                     {1,1},{-1,-1},{1,-1},{-1,1}};
  float offsetG[2] = {1.0,1.414};

  //printf("Initalization Complete\n");
  int debug = 0;
  while(!openList.empty()){
    // Get value from openList
    pPair p = *openList.begin();
    openList.erase(openList.begin());
    //printf("open list size: %ld\n",openList.size());
    // Get indexing
    i = p.second.second; // y,row
    j = p.second.first;  // x,col
    index = i*COL+j;

    //printf("Start[%d,%d]@%d = %.3f\n",i,j,index,p.first);
   
    // Close cell in closed List 
    closedList[index] = true;
    double gNew, hNew, fNew;
    
    for(int k = 0; k <8;k++){ 
      int offseti = i + offset[k][1]; // y offset
      int offsetj = j + offset[k][0]; // x offset
      int offsetIndex = offseti*COL + offsetj;
      
      if(isValid(offseti, offsetj,ROW,COL)){
        //printf("isvalid!\n");
        // reached destination
        if(isDestination(offseti,offsetj,destEnd)){
          cellDetails[offsetIndex]->parent_i = i;
          cellDetails[offsetIndex]->parent_j = j;
          //printf("The destination cell is found\n");
          tracePath(cellDetails, start, destEnd, ROW, COL,tileWidth);
          foundDest = true;
          return; 
        }
        else if(!closedList[offsetIndex] && isUnBlocked(tiles,offseti,offsetj,COL)){
          gNew = cellDetails[index]->g + offsetG[k/4];
          hNew = calculateHValue(offseti,offsetj,destEnd);
          fNew = gNew + hNew;
          //printf("new g, h, f = %f, %f, %f\n",gNew,hNew,fNew); 
          if((cellDetails[offsetIndex]->f == FLT_MAX) || (cellDetails[offsetIndex]->f > fNew)){
            //printf("Found better cost than %f.\n",cellDetails[offsetIndex]->f);
            //printf("Inserted[%d,%d]@%d=%f->%f\n",offseti,offsetj,offsetIndex,cellDetails[offsetIndex]->f,fNew);

            openList.insert(std::make_pair(fNew,std::make_pair(offsetj,offseti)));
            cellDetails[offsetIndex]->f = fNew;
            cellDetails[offsetIndex]->g = gNew;
            cellDetails[offsetIndex]->h = hNew;
            cellDetails[offsetIndex]->parent_i = i;
            cellDetails[offsetIndex]->parent_j = j;
          }
        }
      }
    }
  }

  for(i = 0; i < ROW; i++){
    for(j = 0; j < COL; j++){
      index = i*COL+j;
      free(cellDetails[index]);
    }
  }
  free(cellDetails);

  //if(!foundDest) printf("Failed to find the Destination Cell\n");
  return;
}

void unit::setDestination(double x, double y, Tile** tiles, int mapX, int mapY){

  // empty previous entries  
  std::queue<Pair>empty;
  std::swap(dest,empty);  

  int tileWidth = tiles[0]->getBox().w;

  // start{x,y}
  Pair start = {mCircle.x/tileWidth, mCircle.y/tileWidth};
  Pair destEnd = {x/tileWidth,y/tileWidth};

  if(tiles[destEnd.first+destEnd.second*mapX]->getType()>0) return;

  //printf("%d,%d -> %d,%d\n",start.first,start.second,destEnd.first,destEnd.second);
  
  // A* algorithm
  aStarSearch(tiles,start,destEnd, mapY,mapX);

//  dest.push(Pair{tileWidth*destEnd.first+mCircle.r,tileWidth*destEnd.second+mCircle.r});
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
      //printf("Remove Node {%d,%d}\n",destX,destY);
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
