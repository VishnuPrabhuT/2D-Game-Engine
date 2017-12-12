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
  for (auto sprite:sprites){
    delete sprite;
  }

  for (auto sprite:explosionSprites){
    delete sprite;
  }

  for (auto strategy:strategies){
    delete strategy;
  }
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
  explosionSprites(),
  explosion(false),
  endTime(0),
  currentExplosion(0),
  currentStrategy(Gamedata::getInstance().getXmlInt("CollisionStrategy/PerPixelCollisionStrategy")),
  playerCollision(false),
  gameOver(false),
  currentSprite(0),
  showHUD(true),
  initialFlag(true),
  sound(),
  makeVideo( false )
{
  Vector2f pos = player->getPosition();
  int w = player->getScaledWidth();
  int h = player->getScaledHeight();
  sprites.push_back( new SmartSprite("BlueMonsterRight", pos, w, h) );
  sprites.push_back( new SmartSprite("BlueMonsterGroundRight", pos, w, h) );
  sprites.push_back( new SmartSprite("BlackMonsterRight", pos, w, h) );
  sprites.push_back( new SmartSprite("OrangeMonsterRight", pos, w, h) );
  for (auto sprite : sprites) {
    player->attach( sprite );
  }

  explosionSprites.push_back(new MultiSprite("WaterExplosion"));
  explosionSprites.push_back(new MultiSprite("BlackExplosion"));
  explosionSprites.push_back(new MultiSprite("PlayerExplosion"));

  strategies.push_back( new RectangularCollisionStrategy );
  strategies.push_back( new PerPixelCollisionStrategy );
  strategies.push_back( new MidPointCollisionStrategy );

  Viewport::getInstance().setObjectToTrack(player);
  std::cout << "Loading complete" << std::endl;
}

void Engine::draw() {
  hills1.draw();
  hills2.draw();
  hills3.draw();
  hills4.draw();
  hills5.draw();

  for ( const Drawable* sprite : sprites ) {
    sprite->draw();
    if (clock.getTicks()<endTime){
      explosionSprites[currentExplosion]->draw();
    }
  }
  strategies[currentStrategy]->draw();

  if (!gameOver) {
    player->draw();
  }

  if(showHUD){
    IOmod::getInstance().writeText("FreeList - "+std::to_string(player->freeCount()), 650, 70);
    IOmod::getInstance().writeText("BulletList - "+std::to_string(player->bulletCount()), 650, 93);
    int width=hud.getWidth();
    int height=hud.getHeight();
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_Rect body = {width, height, 220, 175};
    SDL_RenderFillRect( renderer, &body );
    const std::string& s = hud.getText();
    std::istringstream ss(s);
    std::string token;
    int y=150;
    while(std::getline(ss, token, '$')) {
      y+=25;
      io.writeText(token, 30, y,{0xff, 0, 0, 0});
    }
  }
  if ( gameOver ) {
    io.writeText("Game Over!", 300, 120);
    io.writeText("Press R to Restart the game", 250, 200);
  }
  viewport.draw();
  SDL_RenderPresent(renderer);
}

void Engine::checkForCollisions() {
  std::vector<SmartSprite*>::iterator it = sprites.begin();
  while(it != sprites.end()){
    if ( strategies[currentStrategy]->execute(*player, **it) ) {
      gameOver=true;
      playerCollision=true;
      currentExplosion=2;
      endTime=clock.getTicks()+2000;
      explosionSprites[currentExplosion]->setPosition(player->getPosition());
      player->setPosition(Vector2f(Gamedata::getInstance().getXmlInt("IdleRight/startLoc/x"),
               Gamedata::getInstance().getXmlInt("IdleRight/startLoc/y")));
    }
    else {
      ++it;
    }
  }
  for(auto sprite : sprites) {
    std::list<Bullet>& bulletsNPC = sprite->getBulletList();
      for(auto bullet : bulletsNPC){
        if ( strategies[currentStrategy]->execute(*player, bullet) ) {
          gameOver=true;
          playerCollision=true;
          currentExplosion=2;
          endTime=clock.getTicks()+2000;
          explosionSprites[currentExplosion]->setPosition(player->getPosition());
          player->setPosition(Vector2f(Gamedata::getInstance().getXmlInt("IdleRight/startLoc/x"),
                   Gamedata::getInstance().getXmlInt("IdleRight/startLoc/y")));
        }
        else {
          ++it;
        }
      }
  }
}

void Engine::checkBulletCollisions() {
  std::list<Bullet>& bullets = player->getBulletList();
  std::vector<SmartSprite*>::iterator it = sprites.begin();
  for (Bullet& bullet : bullets) {
    while(it != sprites.end()) {
      if ( strategies[currentStrategy]->execute(bullet, **it) ) {
        //collision=true;
        SmartSprite* doa = *it;
        doa->explode();
        if (doa->getName().find("Blue")!=std::string::npos){
          explosion=true;
          endTime=clock.getTicks()+2000;
          currentExplosion=0;
        }
        if (doa->getName().find("Black")!=std::string::npos){
          explosion=true;
          endTime=clock.getTicks()+2000;
          currentExplosion=1;
        }
        player->detach(doa);
        delete doa;
        it=sprites.erase(it);
      }
      else {
        ++it;
      }
    }
  }
}

void Engine::update(Uint32 ticks) {
  if ( playerCollision ) {
    explosionSprites[currentExplosion]->update( ticks );
    if (endTime<clock.getTicks()) {
      playerCollision=false;
      clock.pause();
      gameOver=false;
    }
  }

  player->update(ticks);
  if (Clock::getInstance().getTicks()%25==0) {
    for(SmartSprite* sprite : sprites){
      sprite->shoot();
    }
  }
  IOmod::getInstance().writeText("FreeList - "+std::to_string(player->freeCount()), 700, 70);
  IOmod::getInstance().writeText("BulletList - "+std::to_string(player->bulletCount()), 700, 93);
  for ( Drawable* sprite : sprites ) {
    sprite->update( ticks );
    if (clock.getTicks()<endTime){
      explosionSprites[currentExplosion]->update( ticks );
    }
    else{
      explosion=false;
    }
  }
  checkBulletCollisions();
  if(!playerCollision) {
    checkForCollisions();
  }
  hills1.update();
  hills2.update();
  hills3.update();
  hills4.update();
  hills5.update();
  viewport.update(); // always update viewport last
}

bool Engine::play() {
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
        if ( keystate[SDL_SCANCODE_P] ) {
          if ( clock.isPaused() ) clock.unpause();
          else clock.pause();
        }
        if ( keystate[SDL_SCANCODE_R] ) {
          clock.unpause();
          return true;
        }
        if ( keystate[SDL_SCANCODE_F1] ) {
          showHUD=!showHUD;
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
      if(keystate[SDL_SCANCODE_C]){
        player->roll();
      }
      if ( keystate[SDL_SCANCODE_S] ) {
        sound[3];
        player->shoot();
      }
      draw();
      update(ticks);
      if ( makeVideo ) {
        frameGen.makeFrame();
      }
    }
  }
  return false;
}
