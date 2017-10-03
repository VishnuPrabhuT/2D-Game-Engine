#include <string>
#include <SDL.h>
#include<iostream>

class BlackCat{
public:
	BlackCat(SDL_Renderer*, SDL_Point, SDL_Color, int, int);
	void drawBlackCat();
	int getWidth() const;
	int getHeight() const;
private:
	SDL_Renderer* renderer;
	SDL_Point center;
	SDL_Color color;	
	const int WINDOW_WIDTH;
	const int WINDOW_HEIGHT;
	BlackCat(const BlackCat&);
};
	std::ostream& operator<<(std::ostream&,const BlackCat&);
