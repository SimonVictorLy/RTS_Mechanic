#include "define.h"

// Global variables
LTexture *gTextures[TOTAL_TEXTURES];
Mix_Music *gMusic[TOTAL_TRACKS];
Mix_Chunk *gSoundEffects[TOTAL_SOUNDS];
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
TTF_Font *gFont = NULL;
SDL_Rect *gTileClips[TOTAL_TILE_SPRITES];

int TOTAL_TILES = 192;


int SPAWN_X = 50;
int SPAWN_Y = 50;

bool init(){
  if(SDL_Init(SDL_INIT_VIDEO)<0){printf("SDL Error: %s\n",SDL_GetError()); return false;}
   
  gWindow = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if(gWindow == NULL){printf("Window Error: %s\n",SDL_GetError()); return false;}

  gRenderer = SDL_CreateRenderer(gWindow,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if(gRenderer == NULL){printf("Renderer Error %s\n",SDL_GetError()); return false;}
  SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

  int imgFlags = IMG_INIT_PNG;
  if(!(IMG_Init(imgFlags) & imgFlags)){printf("IMG Error %s\n",IMG_GetError()); return false;}
  if(TTF_Init() == -1){printf("TTF Error: %s\n",TTF_GetError()); return false;}
  if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY,MIX_DEFAULT_FORMAT,2,2048)<0){printf("SDL_Mixer Error: %s\n",Mix_GetError());return false;}
  

  return true;
}

bool loadMedia(){
  bool success = true;
  
  // Load Textures 
  gTextures[TEXTURE_A] = new LTexture(gRenderer);
  success &= gTextures[TEXTURE_A]->loadFromFile("blackCircle.png");

  // Load Textures 
  gTextures[TEXTURE_B] = new LTexture(gRenderer);
  success &= gTextures[TEXTURE_B]->loadFromFile("blackTile.png");

  // used for clipping texture maps
  gTileClips[TILE_ALPHA] = new SDL_Rect{0,0,1,1};
  gTileClips[TILE_BLACK] = new SDL_Rect{0,0,TILE_WIDTH,TILE_HEIGHT};
 

  // Load Font
  // gFont = TTF_OpenFont("BebasNeue-Regular.ttf",28);
  // success &= gFont!=NULL;

  // std::string s = "Score";
  // gTextures[SCORE_TEXT] = new LTexture(gRenderer);
  // success &= gTextures[SCORE_TEXT]->loadFromRenderedText( s, SDL_Color{1,1,1}, gFont);
  
  // Load Music
  // gMusic = Mix_LoadMUS("Tetris 99 - Main Theme.mp3");
  // success &= gMusic!=NULL;

  return success;
}

void close(){
  // Close all Textures
  printf("Closing all textures...\n"); 
  for(int i = 0; i < TOTAL_TEXTURES;i++){
    if(gTextures[i]!=NULL) gTextures[i]->free();
  }

  for(int i =0; i < TOTAL_TILE_SPRITES;i++){
    if(gTileClips[i]!=NULL){
      delete(gTileClips[i]);
    }
  }
  // Close all Fonts
  //TTF_CloseFont(gFont);
  //gFont = NULL;

  // Close all Music
  //Mix_FreeMusic(gMusic);
  //gMusic = NULL;
}


void cleanTiles(Tile** tileSet,int n){
  // delete from 0 to n
  for(int i = 0;i<n;i++){
    if(tileSet[i]!=NULL){
      delete(tileSet[i]);
      tileSet[i]=NULL;
    }
  }
  delete(tileSet); 
}

Tile** setTiles(int &total_tiles, LTexture *textureMap){
  bool tilesLoaded = true;

  Tile **tileSet = NULL;

  int x = 0, y = 0;
  std::ifstream map("obstacles.map");
  
  if(map.fail()){
    printf("Unable to load map file!\n");
    return NULL;
  }
  
  int TOTAL_X_TILES = -1;
  int TOTAL_Y_TILES = -1;
  map >> TOTAL_X_TILES;
  map >> TOTAL_Y_TILES;

  if(map.fail()|| TOTAL_X_TILES <=0 || TOTAL_Y_TILES <=0 ){
    printf("Error Loading map size!\n");
    return NULL;
  }

  total_tiles = TOTAL_X_TILES*TOTAL_Y_TILES;
  // allocate memory for tiles
  tileSet = (Tile**) malloc(sizeof(Tile*)*(TOTAL_X_TILES*TOTAL_Y_TILES)); 

  for(int i = 0; i < TOTAL_Y_TILES; i++){
    for(int j = 0; j < TOTAL_X_TILES; j++){ 

      int tileType = -1;
      int tileIndex = i*TOTAL_X_TILES+j;
      
      //printf("tileIndex(%d,%d): %d\n",i,j,tileIndex);
      map >> tileType;
      if (map.fail()){
        printf("Error loading map: Unexpected end of file!\n");
        cleanTiles(tileSet, tileIndex); 
        return NULL;
      }
    
      // Place tile at x,y
      if((tileType >=0) && (tileType < TOTAL_TILE_SPRITES)){
        tileSet[tileIndex] = new Tile(j*TILE_WIDTH,i*TILE_HEIGHT,tileType,textureMap,gTileClips[tileType]);
      }
      else{
        printf("Error Loading Map: Invalid tile type at %d!\n", i);
        cleanTiles(tileSet, tileIndex); 
        return NULL;
      }
    }
  }


  //Close the file
  map.close();

  //If the map was loaded fine
  return tileSet;
}


int handleInputs(SDL_Event &e, StateTypes &state){
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 ){
    // Key pressed
    switch( e.key.keysym.sym ){
      case SDLK_UP: break;
      case SDLK_DOWN: break;
      case SDLK_LEFT: break;
      case SDLK_RIGHT: break;
      case SDLK_z: break;
      case SDLK_x: break;
    }
  }
  else if( e.type == SDL_KEYUP && e.key.repeat == 0 ){
    // Key released
    switch( e.key.keysym.sym ){
      case SDLK_UP: break;
      case SDLK_DOWN: break;
      case SDLK_LEFT: break;
      case SDLK_RIGHT: break;
    }
  }
  else if( e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP ){
    int x, y;
		SDL_GetMouseState( &x, &y );

		//Set mouse over sprite
		switch( e.type ){
			case SDL_MOUSEMOTION:
        if(x > SCREEN_WIDTH || x < 0 || y>SCREEN_HEIGHT || y < 0) 
          SDL_SetRelativeMouseMode(SDL_TRUE);
        else
          SDL_SetRelativeMouseMode(SDL_FALSE);
        break;	
			case SDL_MOUSEBUTTONDOWN: break;
			case SDL_MOUSEBUTTONUP: break;
		}
	}
}

bool handlePrint(bool success){
  if(success) printf("\033[1;32mSuccess\n\033[0m"); 
  else printf("\033[1;31mFailed\n\033[0m");
  return success;
}

int main(int argc, char *argv[]){
  printf("Initializing... \t");
  if(!handlePrint(init())) return 0;
 
  printf("Loading Media...\t");
  if(!handlePrint(loadMedia())) return 0;  


  bool quit = false; 
  SDL_Event e;
  StateTypes state = MAIN_MENU; 
  SDL_Rect camera = {0,0,SCREEN_WIDTH, SCREEN_HEIGHT};
  selection mouseSelect(gRenderer,NULL);
  
  printf("Loading Map...  \t"); 
  int TOTAL_TILES = 0;
  Tile** tileSet = setTiles(TOTAL_TILES,gTextures[TEXTURE_B]);
  if(!handlePrint(TOTAL_TILES!=0 && tileSet!=NULL)) return 0;

  unit *gUnits[5];
  for(int i = 0; i<5;i++){
    // set texture and unique ID
    gUnits[i] = new unit(gTextures[TEXTURE_A], i, i*50 + SPAWN_X, SPAWN_Y);
  }

  while(!quit){ 
    
    // Handle all inputs
    while(SDL_PollEvent(&e)!=0){
      if(e.type == SDL_QUIT) quit = true;
      handleInputs(e,state);
      mouseSelect.handleEvents(e,gUnits);
    }
    
       // Clear Previous Rendering colors
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF,0xFF,0xFF);  // Background color
    SDL_RenderClear(gRenderer);
   
    // Update objects
    for(int i = 0; i<5;i++){
      gUnits[i]->move(gUnits,tileSet,TOTAL_TILES);
      gUnits[i]->render(camera);
    }
    
    mouseSelect.render(camera,false);

    for(int i = 0; i<TOTAL_TILES;i++){
      tileSet[i]->render(camera);
    }

    // Render based on Game State
    switch(state){
      case(MAIN_MENU): break;
      case(INITIALIZE): break;
      case(PLAYING): break;
      case(GAME_OVER): break;
    };

    SDL_RenderPresent(gRenderer);
  }

  close();
  cleanTiles(tileSet,TOTAL_TILES);
  return 0;
}
