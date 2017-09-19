#include<SDL.h>
#include "frameGenerator.h"

const int WINDOW_WIDTH=750;
const int WINDOW_HEIGHT=500;
class BlackCat{
public:
	BlackCat(){
				
	}	
	BlackCat(SDL_Renderer* rend,SDL_Point cen,SDL_Color col):renderer(rend),center(cen),color(col){
			
	}
	void drawSaiyin(){
		SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
		SDL_Rect body = {center.x+15, center.y-0, 150, 175};
	  	SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
	  	SDL_RenderFillRect( renderer, &body );
	
		SDL_Rect head = {center.x-35, center.y-200, 250, 200};
	  	SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
	  	SDL_RenderFillRect( renderer, &head );

		SDL_Rect mouth = {center.x+15, center.y-75, 150, 60};
	  	SDL_SetRenderDrawColor( renderer, 255, 80, 80, 255/2 );
	  	SDL_RenderFillRect( renderer, &mouth );

		SDL_Point v1={center.x+24,center.y+25};
		SDL_Point v2={center.x+51,center.y+25};
		SDL_Point v3={center.x+14,center.y+10};	
		SDL_SetRenderDrawColor(renderer,255,255,255,255);
		SDL_RenderDrawLine(renderer, v1.x, v1.y, v2.x, v2.y);
		SDL_RenderDrawLine(renderer, v2.x, v2.y, v3.x, v3.y);
		SDL_RenderDrawLine(renderer, v3.x, v3.y, v1.x, v1.y);
	
		//SDL_SetRenderDrawColor(renderer,254,254,20,255);
		for (int w = 0; w < EYE_RADIUS * 2; w++) {
	    		for (int h = 0; h < EYE_RADIUS * 2; h++) {
	      			int dx = EYE_RADIUS - w;
	      			int dy = EYE_RADIUS - h;
	      			if ((dx*dx + dy*dy) <= (EYE_RADIUS * EYE_RADIUS)) {
					SDL_SetRenderDrawColor(renderer,254,254,20,255);
					SDL_RenderDrawPoint(renderer, center.x + dx+37, center.y + dy-140);
					SDL_RenderDrawPoint(renderer, center.x + dx+143, center.y + dy-140);
					if((dx*dx + dy*dy) <= ((EYE_RADIUS * EYE_RADIUS)*3)/4){
						SDL_SetRenderDrawColor(renderer,0,0,0,255);
						SDL_RenderDrawPoint(renderer, center.x + dx+37, center.y + dy-140);
						SDL_RenderDrawPoint(renderer, center.x + dx+143, center.y + dy-140);
					}
	      			}
	    		}
	  	}

	
	}
private:
	const int EYE_RADIUS=40;
	SDL_Renderer* renderer;
	SDL_Point center;
	SDL_Color color;
};
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
	  	
	BlackCat blacky(renderer,center,color);
	blacky.drawSaiyin();

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
