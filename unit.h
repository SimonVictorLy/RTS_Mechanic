class unit{
public:
  unit(LTexture *inTexture,int unitID, int initX, int initY);

  int id;
  void move(unit *gUnits[], Tile **tiles, int tileCount);
  void setDestination(double x, double y);
  void render(SDL_Rect &camera);
  void handleEvents(SDL_Event &e);
  bool unitCollides(unit *gUnits[]);
  bool wallCollides(Tile ** tiles, int tileCount);
  int getX();
  int getY();

private:
  Circle mCircle;

  int destX, destY;
  static const int UNIT_WIDTH = 50;
  double mVel = 10.0;
  LTexture *texture;

  friend class selection;
};
