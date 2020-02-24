class unit{
public:
  unit(LTexture *inTexture,int unitID, int initX, int initY);

  int id;
  void move(unit *gUnits[], Tile **tiles, int tileCount);
  void setDestination(double x, double y, Tile **tiles, int mapX, int mapY);
  void render(SDL_Rect &camera);
  void handleEvents(SDL_Event &e);
  bool unitCollides(unit *gUnits[]);
  bool wallCollides(Tile ** tiles, int tileCount);
  int getX();
  int getY();

private:
  Circle mCircle;

  std::queue<std::pair<int,int>> dest;
  int destX, destY;
  static const int UNIT_WIDTH = 50;
  double mVel = 10.0;
  LTexture *texture;

// A* functions
  bool isValid(int row, int col, int ROW, int COL);
  bool isUnBlocked(Tile ** tiles, int row, int col, int ROW);
  bool isDestination(int row, int col, Pair dest); 
  double calculateHValue(int row, int col, Pair dest);
  void tracePath(cell **cellDetails, Pair dest);

  void aStarSearch(Tile **tiles,  Pair start, Pair destEnd, int ROW, int COL);
  friend class selection;
};
