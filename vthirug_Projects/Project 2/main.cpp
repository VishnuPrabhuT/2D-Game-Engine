#include<SDL.h>
#include "BlackCat.h"

const int WINDOW_WIDTH=700;
const int WINDOW_HEIGHT=700;
const int EYE_RADIUS=40;

int main(void){
	if ( SDL_Init(SDL_INIT_VIDEO) != 0 ) {
    		std::cout << "Failed to initialize SDL2" << std::endl;
    		return EXIT_FAILURE;
  	}
	SDL_Renderer* renderer;
  	SDL_Window* window = SDL_CreateWindow(
      				"Drawing a Triangle", SDL_WINDOWPOS_UNDEFINED,
      				SDL_WINDOWPOS_UNDEFINED,
      				WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN
  			      );
  	//SDL_Init(SDL_INIT_VIDEO);
  	SDL_CreateWindowAndRenderer(
    		WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer
  	);

  	SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
  	SDL_RenderClear(renderer);

	
  	SDL_Point center = {250, 350};
  	SDL_Color color = {0,0,0,255};
	  	
	BlackCat blacky(renderer,center,color,WINDOW_WIDTH,WINDOW_HEIGHT,EYE_RADIUS);
	blacky.drawBlackCat();

  	SDL_RenderPresent(renderer);
	SDL_Event event;
  	const Uint8* keystate;
  	while ( true ) {
    		keystate = SDL_GetKeyboardState(0);
    		if (keystate[SDL_SCANCODE_ESCAPE]) { break; }
    		if (SDL_PollEvent(&event)) {
      			if (event.type == SDL_QUIT) {
        			break;
      			}
    		}
  	}
	SDL_DestroyRenderer(renderer);
  	SDL_DestroyWindow(window);
  	SDL_Quit();
}
