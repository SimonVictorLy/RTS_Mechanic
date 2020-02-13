#include "define.h"

bool checkCollision(SDL_Rect &a, SDL_Rect &b){
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

bool checkCollision( Circle& a, Circle& b ){
	//Calculate total radius squared
	int totalRadiusSquared = a.r + b.r;
	totalRadiusSquared = totalRadiusSquared * totalRadiusSquared;


  return distanceSquared( a.x, a.y, b.x, b.y ) < totalRadiusSquared;
}

bool checkCollision( Circle& a, SDL_Rect& b )
{
    // Closest point on collision box
    int cX, cY;

    // Find closest x offset
    if( a.x < b.x ) cX = b.x;
    else if( a.x > b.x + b.w ) cX = b.x + b.w;
    else cX = a.x;

    // Find closest y offset
    if( a.y < b.y ) cY = b.y;
    else if( a.y > b.y + b.h ) cY = b.y + b.h;
    else cY = a.y;

    //If the closest point is inside the circle
    return ( distanceSquared( a.x, a.y, cX, cY ) < a.r * a.r );
}

double distanceSquared( int x1, int y1, int x2, int y2 ){
	int deltaX = x2 - x1;
	int deltaY = y2 - y1;
	return deltaX*deltaX + deltaY*deltaY;
}

