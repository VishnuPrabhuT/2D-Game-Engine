#include<SDL.h>
#include "frameGenerator.h"

const int WINDOW_WIDTH=750;
const int WINDOW_HEIGHT=500;
const int EYE_RADIUS=32;

void drawSaiyin(SDL_Renderer* renderer,SDL_Point center,SDL_Color color){
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	
	//SDL_RenderDrawLine(renderer, center.x+65, center.y+0, center.x+50, center.y+75);
	//SDL_RenderDrawLine(renderer, center.x-65, center.y+0, center.x-50, center.y+75);
	//SDL_RenderDrawLine(renderer, center.x-65, center.y+0, center.x-50, center.y+75);

	//SDL_RenderDrawLine(renderer, center.x+50, center.y+75, center.x+0, center.y+100);
	//SDL_RenderDrawLine(renderer, center.x-50, center.y+75, center.x+0, center.y+100);
	//SDL_RenderDrawLine(renderer, 300, 240, 340, 240);
  	//SDL_RenderDrawLine(renderer, 340, 240, 320, 200);
	SDL_Rect body = {center.x+15, center.y-0, 150, 175};
  	SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
  	SDL_RenderFillRect( renderer, &body );
	
	SDL_Rect head = {center.x-10, center.y-200, 200, 200};
  	SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
  	SDL_RenderFillRect( renderer, &head );
	
	SDL_SetRenderDrawColor(renderer,254,254,20,255);
	for (int w = 0; w < EYE_RADIUS * 2; w++) {
    		for (int h = 0; h < EYE_RADIUS * 2; h++) {
      			int dx = EYE_RADIUS - w;
      			int dy = EYE_RADIUS - h;
      			if ((dx*dx + dy*dy) <= (EYE_RADIUS * EYE_RADIUS)) {
        			SDL_RenderDrawPoint(renderer, center.x + dx+37, center.y + dy-140);
				SDL_RenderDrawPoint(renderer, center.x + dx+137, center.y + dy-140);
      			}
    		}
  	}

	
}

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

	
  	SDL_Point center = {250, 250};
  	SDL_Color color = {0,0,0,255};
	  	
	drawSaiyin(renderer, center, color);

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
