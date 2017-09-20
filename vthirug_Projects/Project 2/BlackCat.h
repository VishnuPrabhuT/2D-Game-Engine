#include <string>
#include <SDL.h>
#include<iostream>

class BlackCat{
public:
	BlackCat(SDL_Renderer*, SDL_Point, SDL_Color, int, int, int);
	void drawBlackCat();
private:
	SDL_Renderer* renderer;
	SDL_Point center;
	SDL_Color color;	
	const int WINDOW_WIDTH;
	const int WINDOW_HEIGHT;
	const int EYE_RADIUS;
	BlackCat(const BlackCat&);
	BlackCat& operator=(const BlackCat&);
};
