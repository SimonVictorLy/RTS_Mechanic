#include "define.h"

// Global variables
LTexture *gTextures[TOTAL_TEXTURES];
Mix_Music *gMusic[TOTAL_TRACKS];
Mix_Chunk *gSoundEffects[TOTAL_SOUNDS];
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
TTF_Font *gFont = NULL;

bool tileMap[SCREEN_HEIGHT/TILE_HEIGHT][SCREEN_WIDTH/TILE_WIDTH];

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
  for(int i = 0; i < TOTAL_TEXTURES;i++){
    if(gTextures[i]!=NULL) gTextures[i]->free();
  }

  // Close all Fonts
  //TTF_CloseFont(gFont);
  //gFont = NULL;

  // Close all Music
  //Mix_FreeMusic(gMusic);
  //gMusic = NULL;
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
			case SDL_MOUSEMOTION: break;	
			case SDL_MOUSEBUTTONDOWN: break;
			case SDL_MOUSEBUTTONUP: break;
		}
	}
}



int main(int argc, char *argv[]){
  if(!init()){ printf("Failed to Initialize!\n"); return 0;}
  if(!loadMedia()){printf("Failed to load Media\n"); return 0;}
 
  SDL_Event e;
  bool quit = false; 
  StateTypes state = MAIN_MENU; 
  SDL_Rect camera = {0,0,SCREEN_WIDTH, SCREEN_HEIGHT};


  selection mouseSelect(gRenderer,NULL);

  unit *gUnits[5];

  for(int i = 0; i<5;i++){
    // set texture and unique ID
    gUnits[i] = new unit(gTextures[TEXTURE_A], i, i*50+50, i*50+50);
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
      gUnits[i]->move(gUnits);
      gUnits[i]->render(camera);
    }
    
    mouseSelect.render(camera,false);


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
  return 0;
}
