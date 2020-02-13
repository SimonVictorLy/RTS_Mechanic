class unit{
public:
  unit(LTexture *inTexture);

  void move();
  void setDestination(double x, double y);
  void render(SDL_Rect &camera);
  void handleEvents(SDL_Event &e);
  int getX();
  int getY();

private:
  SDL_Rect mBox;
  int destX, destY;
  static const int UNIT_WIDTH = 50;
  static const int UNIT_HEIGHT = 50;
  double mVel = 10.0;
  LTexture *texture;

  friend class selection;
};
