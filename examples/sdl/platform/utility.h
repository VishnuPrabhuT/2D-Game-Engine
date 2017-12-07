#pragma once

#include <SDL.h>

void ColorSubstitute(SDL_Surface* surface, const SDL_Color colorFrom, const SDL_Color colorTo);

inline Uint32 getpixel(SDL_Surface* surface, int x, int y)
{
  const int bpp = surface->format->BytesPerPixel;
  Uint8* p = reinterpret_cast<Uint8*>(surface->pixels) + y*surface->pitch + x*bpp;

  switch(bpp){
    case 1: return *p;
    case 2: return *reinterpret_cast<Uint16*>(p);
    case 3: return SDL_BYTEORDER == SDL_BIG_ENDIAN
                 ? p[0] << 16 | p[1] << 8 | p[2]
                 : p[0]       | p[1] << 8 | p[2] << 16;
    case 4: return *reinterpret_cast<Uint32*>(p);
  }

  return 0;
}

inline void putpixel(SDL_Surface* surface, int x, int y, Uint32 pix)
{
  const int bpp = surface->format->BytesPerPixel;
  Uint8* p = reinterpret_cast<Uint8*>(surface->pixels) + y*surface->pitch + x*bpp;

  switch(bpp){
    case 1:
      *p = pix;
      break;
    case 2:
      *reinterpret_cast<Uint16*>(p) = pix;
      break;
    case 3:
      if(SDL_BYTEORDER == SDL_BIG_ENDIAN){
        p[0] = (pix >> 16) & 0xff;
        p[1] = (pix >> 8)  & 0xff;
        p[2] = (pix)       & 0xff;
      }else{
        p[2] = (pix >> 16) & 0xff;
        p[1] = (pix >> 8)  & 0xff;
        p[0] = (pix)       & 0xff;
      }
    case 4:
      *reinterpret_cast<Uint32*>(p) = pix;
      break;
  }
}
