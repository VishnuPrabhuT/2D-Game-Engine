#include "utility.h"

void ColorSubstitute(SDL_Surface* surface, const SDL_Color colorFrom, const SDL_Color colorTo)
{
  const int W = surface->w;
  const int H = surface->h;

  const Uint32 from = SDL_MapRGBA(surface->format, colorFrom.r, colorFrom.g, colorFrom.b, colorFrom.a);
  const Uint32 to = SDL_MapRGBA(surface->format, colorTo.r, colorTo.g, colorTo.b, colorTo.a);

  for(int x = 0; x < W; ++x){
    for(int y = 0; y < H; ++y){
      if(getpixel(surface, x, y) == from){
        putpixel(surface, x, y, to);
      }
    }
  }
}
