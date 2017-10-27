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
#include "player.h"

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
  hills1("hills1", Gamedata::getInstance().getXmlInt("hills1/factor") ),
  hills2("hills2", Gamedata::getInstance().getXmlInt("hills2/factor") ),
  hills3("hills3", Gamedata::getInstance().getXmlInt("hills3/factor") ),
  hills4("hills4", Gamedata::getInstance().getXmlInt("hills4/factor") ),
  hills5("hills5", Gamedata::getInstance().getXmlInt("hills5/factor") ),
  viewport( Viewport::getInstance() ),
  player(new Player("Charizard")),
  currentSprite(0),
  makeVideo( false )
{
  //polyVector.reserve(4);
  //polyVector.emplace_back(new TwoWayMultiSprite("Charizard"));
  //polyVector.emplace_back(new MultiSprite("Goku"));
  //polyVector.emplace_back(new MultiSprite("Aura"));
  //polyVector.emplace_back(new Sprite("ShockMe"));
  Viewport::getInstance().setObjectToTrack(player);
  std::cout << "Loading complete" << std::endl;
}

void Engine::draw() const {
  hills1.draw();
  hills2.draw();
  hills3.draw();
  hills4.draw();
  hills5.draw();

  for (auto sprite:polyVector){
    sprite->draw();  
  }
  
  //spinningStar->draw();
  player->draw();
  viewport.draw();
  SDL_RenderPresent(renderer);
}

void Engine::update(Uint32 ticks) {
  player->update(ticks);
  for (auto sprite:polyVector)
  {
    sprite->update(ticks);  
  }
  //star->update(ticks);
  //spinningStar->update(ticks);
  hills1.update();
  hills2.update();
  hills3.update();
  hills4.update();
  hills5.update();
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
      if(keystate[SDL_SCANCODE_A]){
        player->left();
      }
      if(keystate[SDL_SCANCODE_D]){
        player->right();
      }
      if(keystate[SDL_SCANCODE_W]){
        player->up();
      }
      if(keystate[SDL_SCANCODE_S]){
        player->down();
      }
      draw();
      update(ticks);
      if ( makeVideo ) {
        frameGen.makeFrame();
      }
    }
  }
}
