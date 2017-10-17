#include”renderContext.h”



SDLWindow∗ RenderContext::initWindow(){
	window=SDLCreateWindow(”HelloWorld”,SDLWINDOWPOSCENTERED,
	SDLWINDOWPOSCENTERED,WIDTH,HEIGHT,SDLWINDOWSHOWN);
	if(window==NULL){
		throw(std::string(”Couldn’tmakeawindow:”)+SDLGetError());
	}
	returnwindow;
}
