class selection {
  public:
    selection(SDL_Renderer* gRenderer, LTexture *texture);
    
    void moveSelected(); 
    void render(SDL_Rect& camera,bool center);
    void select(unit *gUnits[]);
    void handleEvents(SDL_Event &e, unit *gUnits[]);

    int getX();
    int getY();

  private:
    SDL_Rect mBox;
    SDL_Renderer* renderer;
    std::vector<unit*> selected;
    bool leftButton;
    LTexture* mTexture;
};


