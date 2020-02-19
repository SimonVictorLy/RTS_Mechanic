#ifndef _Tile_H
#define _Tile_H

class Tile
{
  public:
    Tile(int x,int y,int tileType, LTexture* textureMap, SDL_Rect *typeSelect);
    void render(SDL_Rect &camera);
    int getType();
    SDL_Rect getBox();

  private:
    int mType;
    SDL_Rect mBox;
    LTexture *mTexture;
    SDL_Rect *mClip;
};

#endif
