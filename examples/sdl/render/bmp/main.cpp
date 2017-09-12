// The basis of this example was obtained from:
// https://wiki.libsdl.org/SDL_CreateRenderer
// The original example was modified by Brian Malloy, Jan 2017

#include <iostream>
#include "SDL.h"

int main( ) {
  int posX = 100, posY = 100, width = 320, height = 240;
  SDL_Init(SDL_INIT_VIDEO);

  SDL_Window *win = 
    SDL_CreateWindow("Hello World", posX, posY, width, height, 0);

  SDL_Renderer *renderer = 
    SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

  SDL_Surface *surface = SDL_LoadBMP("images/hello.bmp");
  if ( !surface ) {
    std::cout << "Couldn't load images/hello.bmp" << std::endl;
    return 1;
  }

  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);

  while ( true ) {
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        break;
      }
    }

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
  }

  SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(win);

  SDL_Quit();
}
