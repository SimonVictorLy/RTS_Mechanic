#ifndef COLLISIONS_HEADER_
#define COLLISIONS_HEADER_

namespace collisions{
  bool checkCollision( SDL_Rect &a, SDL_Rect &b);
  bool checkCollision( Circle& a, Circle& b );
  bool checkCollision( Circle& a, SDL_Rect& b );

  double distanceSquared( int x1, int y1, int x2, int y2 );
}
#endif
