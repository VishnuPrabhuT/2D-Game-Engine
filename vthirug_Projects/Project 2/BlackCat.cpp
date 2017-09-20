#include<SDL.h>
#include<iostream>
#include <cmath>
#include "BlackCat.h"
	
BlackCat::BlackCat(SDL_Renderer* rend,SDL_Point cen,SDL_Color col,int width,int height,int eyeRad):renderer(rend),center(cen),color(col),WINDOW_WIDTH(width),WINDOW_HEIGHT(height),EYE_RADIUS(eyeRad){
			
}

void BlackCat::drawBlackCat(){
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_Rect body = {center.x+15, center.y-0, 150, 175};
  	SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
  	SDL_RenderFillRect( renderer, &body );

	int radius=60;
	for (int s=0;s<radius*2;s++){
		for (int r=0;r<radius*2;r++){
			int dx=radius-s;
			int dy=radius-r;
			if ((dx*dx + dy*dy) <= (radius * radius)) {
				SDL_SetRenderDrawColor(renderer,0,0,0,255);
				SDL_RenderDrawPoint(renderer, center.x + dx+5, center.y + dy-200);
				SDL_RenderDrawPoint(renderer, center.x + dx+175, center.y + dy-200);
				if((dx*dx + dy*dy) <= ((EYE_RADIUS * EYE_RADIUS)*3)/4){
					SDL_SetRenderDrawColor(renderer, 255, 80, 80,255);
					SDL_RenderDrawPoint(renderer, center.x + dx+5, center.y + dy-200);
					SDL_RenderDrawPoint(renderer, center.x + dx+175, center.y + dy-200);		
				}			
			}			
		}	
	}

	SDL_Rect head = {center.x-35, center.y-200, 250, 200};
  	SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
  	SDL_RenderFillRect( renderer, &head );
	
	SDL_Point v1={center.x+75,center.y-90};
	SDL_Point v2={center.x+105,center.y-90};
	SDL_Point v3={center.x+90,center.y-75};
	SDL_SetRenderDrawColor(renderer,255,255,255,255);
	SDL_RenderDrawLine(renderer, v1.x, v1.y, v2.x, v2.y);
	SDL_RenderDrawLine(renderer, v2.x, v2.y, v3.x, v3.y);
	SDL_RenderDrawLine(renderer, v3.x, v3.y, v1.x,v1.y);

	SDL_RenderDrawLine(renderer, v3.x, v3.y, v3.x,v1.y+35);
	SDL_RenderDrawLine(renderer, v3.x, v1.y+35, v3.x+30,v1.y+25);
	SDL_RenderDrawLine(renderer, v3.x, v1.y+35, v3.x-30,v1.y+25);

	
	SDL_RenderDrawLine(renderer, v3.x+20, v3.y+5,v3.x+80,v3.y-30);
	SDL_RenderDrawLine(renderer, v3.x-20, v3.y+5,v3.x-80,v3.y-30);
	SDL_RenderDrawLine(renderer, v3.x+20, v3.y+5,v3.x+80,v3.y-10);
	SDL_RenderDrawLine(renderer, v3.x-20, v3.y+5,v3.x-80,v3.y-10);
	SDL_RenderDrawLine(renderer, v3.x+20, v3.y+5,v3.x+80,v3.y+10);
	SDL_RenderDrawLine(renderer, v3.x-20, v3.y+5,v3.x-80,v3.y+10);

	SDL_Rect tail = {center.x+160, center.y+125, 120, 20};
  	SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
  	SDL_RenderFillRect( renderer, &tail );
		
	SDL_Rect tail2 = {center.x+280, center.y+125, 20, 93};
	SDL_RenderFillRect( renderer, &tail2 );

	SDL_Rect leg1 = {center.x+20, center.y+170, 45, 25};
	SDL_RenderFillRect( renderer, &leg1 );
	SDL_Rect leg2 = {center.x+115, center.y+170, 45, 25};
	SDL_RenderFillRect( renderer, &leg2 );
	


	SDL_SetRenderDrawColor(renderer,254,254,20,255);
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
