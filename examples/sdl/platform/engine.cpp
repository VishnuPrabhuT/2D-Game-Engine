#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <random>
#include <iomanip>
#include "sprite.h"
#include "multisprite.h"
#include "gamedata.h"
#include "engine.h"
#include "frameGenerator.h"

const SDL_Color PINK = {255, 175, 175, 255};

Engine::~Engine() { 
  for ( auto it : sprites ) {
    delete it;
  }
  std::cout << "Terminating program" << std::endl;
}

Engine::Engine() :
  rc( RenderContext::getInstance() ),
  io( IOmod::getInstance() ),
  clock( Clock::getInstance() ),
  gd( Gamedata::getInstance() ),
  renderer( rc->getRenderer() ),

	sky("sky", gd.getXmlInt("sky/factor")),
	hills("hills", gd.getXmlInt("hills/factor")),
  ground("ground", gd.getXmlInt("ground/factor") ),
  crate("crate"),

  viewport( Viewport::getInstance() ),
  bear("bear"),
  sprites(),
  currentSprite(0),
  makeVideo( false )
{
  crate.setScale(0.5);
  int numberOfBirds = Gamedata::getInstance().getXmlInt("numberOfBirds");
  for (int i = 0; i < numberOfBirds; ++i) {
    sprites.push_back( new MultiSprite("vogel") );
  }
  Viewport::getInstance().setObjectToTrack(&bear);
  std::cout << "Loading complete" << std::endl;
}

void Engine::draw() const {
  sky.draw();
	hills.draw();
	ground.draw();
	crate.draw();

  std::stringstream strm;
  strm << "fps: " << clock.getFps();
  io.writeText(strm.str(), 30, 60);
  io.writeText("Platform Demo", PINK, 30, 440);

  for ( Drawable* sprite : sprites ) {
    sprite->draw();
  }
  bear.draw();

  viewport.draw();
  SDL_RenderPresent(renderer);
}

void Engine::update(Uint32 ticks) {
  sky.update();
	hills.update();
  ground.update();

  for ( Drawable* sprite : sprites ) {
    sprite->update(ticks);
  }
  bear.update(ticks);
  viewport.update(); // always update viewport last
}

void Engine::switchSprite(){
  ++currentSprite;
  //currentSprite = currentSprite % sprites.size();
  currentSprite = currentSprite % 2;
  if ( currentSprite ) {
    Viewport::getInstance().setObjectToTrack(sprites[currentSprite]);
  }
  else {
  Viewport::getInstance().setObjectToTrack(&bear);
  }
}

void Engine::play() {
  SDL_Event event;
  const Uint8* keystate;
  bool done = false;
  Uint32 ticks = clock.getElapsedTicks();
  FrameGenerator frameGen;

  while ( !done ) {
    // The next loop polls for events, guarding against key bounce:
    while ( SDL_PollEvent(&event) ) {
      keystate = SDL_GetKeyboardState(NULL);
      if (event.type ==  SDL_QUIT) { done = true; break; }
      if(event.type == SDL_KEYDOWN) {
        if (keystate[SDL_SCANCODE_ESCAPE] || keystate[SDL_SCANCODE_Q]) {
          done = true;
          break;
        }
        if ( keystate[SDL_SCANCODE_P] ) {
          if ( clock.isPaused() ) clock.unpause();
          else clock.pause();
        }
        if ( keystate[SDL_SCANCODE_T] ) {
          switchSprite();
        }
        if (keystate[SDL_SCANCODE_F4] && !makeVideo) {
          std::cout << "Initiating frame capture" << std::endl;
          makeVideo = true;
        }
        else if (keystate[SDL_SCANCODE_F4] && makeVideo) {
          std::cout << "Terminating frame capture" << std::endl;
          makeVideo = false;
        }
      }
    }

    // In this section of the event loop we allow key bounce:

    ticks = clock.getElapsedTicks();
    if ( ticks > 0 ) {
      clock.incrFrame();
      if (keystate[SDL_SCANCODE_J]) {
        bear.jump();
      }
      if (keystate[SDL_SCANCODE_A]) {
        bear.left();
      }
      if (keystate[SDL_SCANCODE_D]) {
        bear.right();
      }
      if (keystate[SDL_SCANCODE_W]) {
        bear.up();
      }
      if (keystate[SDL_SCANCODE_S]) {
        bear.down();
      }
      draw();
      update(ticks);
      if ( makeVideo ) {
        frameGen.makeFrame();
      }
    }
  }
}
