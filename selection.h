class selection {
  public:
    selection(SDL_Renderer* gRenderer, LTexture *texture);
    
    void moveSelected(Tile **tiles, int mapX, int mapY); 
    void render(SDL_Rect& camera,bool center);
    void select(unit *gUnits[]);
    void handleEvents(SDL_Event &e, unit *gUnits[], Tile **tiles, int mapX, int mapY);

    int getX();
    int getY();

  private:
    SDL_Rect mBox;
    SDL_Renderer* renderer;
    std::vector<unit*> selected;
    bool leftButton;
    LTexture* mTexture;
};


