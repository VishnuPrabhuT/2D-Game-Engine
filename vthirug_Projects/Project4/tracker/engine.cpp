#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <random>
#include <iomanip>
#include "sprite.h"
#include "multisprite.h"
#include "twowaymultisprite.h"
#include "gamedata.h"
#include "engine.h"
#include "frameGenerator.h"

Engine::~Engine() { 
  //delete star;
  for (auto sprite:polyVector){
   delete sprite;  
  }
  //delete spinningStar;
  std::cout << "Terminating program" << std::endl;
}

Engine::Engine() :
  rc( RenderContext::getInstance() ),
  io( IOmod::getInstance() ),
  clock( Clock::getInstance() ),
  renderer( rc->getRenderer() ),
  namek("namek", Gamedata::getInstance().getXmlInt("namek/factor") ),
  sky("sky", Gamedata::getInstance().getXmlInt("sky/factor") ),
  viewport( Viewport::getInstance() ),
  currentSprite(0),
  makeVideo( true )
{
  polyVector.reserve(4);
  polyVector.emplace_back(new TwoWayMultiSprite("Charizard"));
  polyVector.emplace_back(new MultiSprite("Goku"));
  polyVector.emplace_back(new MultiSprite("Aura"));
  polyVector.emplace_back(new Sprite("ShockMe"));
  Viewport::getInstance().setObjectToTrack(polyVector.front());
  std::cout << "Loading complete" << std::endl;
}

void Engine::draw() const {
  sky.draw();
  namek.draw();

  for (auto sprite:polyVector){
    sprite->draw();  
  }
  
  //spinningStar->draw();

  viewport.draw();
  SDL_RenderPresent(renderer);
}

void Engine::update(Uint32 ticks) {
  for (auto sprite:polyVector)
  {
    sprite->update(ticks);  
  }
  //star->update(ticks);
  //spinningStar->update(ticks);
  sky.update();
  namek.update();
  viewport.update(); // always update viewport last
}

void Engine::switchSprite(){
  ++currentSprite;
  currentSprite = currentSprite % 2;
  if ( currentSprite ) {
    Viewport::getInstance().setObjectToTrack(polyVector[currentSprite]);
  }
  else {
    Viewport::getInstance().setObjectToTrack(polyVector[currentSprite]);
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
      draw();
      update(ticks);
      if ( makeVideo ) {
        frameGen.makeFrame();
      }
    }
  }
}
