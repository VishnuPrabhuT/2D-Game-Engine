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
#include "collisionStrategy.h"
#include "smartSprite.h"

Engine::~Engine() {
  delete player;
  std::cout << "Terminating program" << std::endl;
}

Engine::Engine() :
  rc( RenderContext::getInstance() ),
  io( IOmod::getInstance() ),
  hud( HUD::getInstance() ),
  clock( Clock::getInstance() ),
  renderer( rc->getRenderer() ),
  hills1("hills1", Gamedata::getInstance().getXmlInt("hills1/factor") ),
  hills2("hills2", Gamedata::getInstance().getXmlInt("hills2/factor") ),
  hills3("hills3", Gamedata::getInstance().getXmlInt("hills3/factor") ),
  hills4("hills4", Gamedata::getInstance().getXmlInt("hills4/factor") ),
  hills5("hills5", Gamedata::getInstance().getXmlInt("hills5/factor") ),
  viewport( Viewport::getInstance() ),
  player(new Player("IdleRight")),
  sprites(),
  strategies(),
  currentStrategy(1),
  collision(false),
  //currentSprite(0),
  showHUD(true),
  initialFlag(true),
  makeVideo( false )
{
  //sprites.reserve(2);
  Vector2f pos = player->getPosition();
  int w = player->getScaledWidth();
  int h = player->getScaledHeight();
  sprites.push_back( new SmartSprite("BlueMonsterRight", pos, w, h) );
  sprites.push_back( new SmartSprite("BlueMonsterGroundRight", pos, w, h) );
  for (int i = 0; i < 2; ++i) {
    player->attach( sprites[i] );
  }

  strategies.push_back( new RectangularCollisionStrategy );
  strategies.push_back( new PerPixelCollisionStrategy );
  strategies.push_back( new MidPointCollisionStrategy );

  Viewport::getInstance().setObjectToTrack(player);
  std::cout << "Loading complete" << std::endl;
}

void Engine::draw() const {
  hills1.draw();
  hills2.draw();
  hills3.draw();
  hills4.draw();
  hills5.draw();

  for ( const Drawable* sprite : sprites ) {
    sprite->draw();
  }

  strategies[currentStrategy]->draw();
  if ( collision ) {
    IOmod::getInstance().writeText("Oops: Collision", 500, 90);
  }

  player->draw();
  if(showHUD){
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_Rect body = {30, 125, 220, 175};
    SDL_RenderFillRect( renderer, &body );

    std::string s = hud.getText();
    std::istringstream ss(s);
    std::string token;
    int y=150;
    while(std::getline(ss, token, '$')) {
      y+=25;
      io.writeText(token, 30, y,{0xff, 0, 0, 0});
    }
  }
  viewport.draw();
  SDL_RenderPresent(renderer);
}

void Engine::checkForCollisions() {
  collision=false;
  std::vector<SmartSprite*>::iterator it = sprites.begin();
  while(it != sprites.end()){
    if ( strategies[currentStrategy]->execute(*player, **it) ) {
      collision=true;
      SmartSprite* doa = *it;
      player->detach(doa);
      delete doa;
      it=sprites.erase(it);
    }
    else{
      ++it;
    }
  }
}

void Engine::update(Uint32 ticks) {
  checkForCollisions();
  player->update(ticks);
  for ( Drawable* sprite : sprites ) {
    sprite->update( ticks );
  }

  hills1.update();
  hills2.update();
  hills3.update();
  hills4.update();
  hills5.update();
  viewport.update(); // always update viewport last
}

void Engine::play() {
  SDL_Event event;
  const Uint8* keystate;
  bool done = false;
  Uint32 ticks = clock.getElapsedTicks();
  FrameGenerator frameGen;

  while ( !done ) {
    // The next loop polls for events, guarding against key bounce:
    if(clock.getTicks()>7500 && initialFlag){
      showHUD=false;
      initialFlag=false;
    }
    while ( SDL_PollEvent(&event) ) {
      keystate = SDL_GetKeyboardState(NULL);
      if (event.type ==  SDL_QUIT) { done = true; break; }
      if(event.type == SDL_KEYDOWN) {
        if (keystate[SDL_SCANCODE_ESCAPE] || keystate[SDL_SCANCODE_Q]) {
          done = true;
          break;
        }
        if ( keystate[SDL_SCANCODE_F1] ) {
          showHUD=!showHUD;
        }
        if ( keystate[SDL_SCANCODE_P] ) {
          if ( clock.isPaused() ) clock.unpause();
          else clock.pause();
        }
        if ( keystate[SDL_SCANCODE_M] ) {
          currentStrategy = (1 + currentStrategy) % strategies.size();
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
      if(keystate[SDL_SCANCODE_SPACE]){
        player->dash();
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
