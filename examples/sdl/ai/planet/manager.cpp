#include <iostream>
#include <string>
#include "subjectsprite.h"
#include "explodingSprite.h"
#include "gamedata.h"
#include "manager.h"

Manager::~Manager() { 
  for (unsigned i = 0; i < sprites.size(); ++i) {
    delete sprites[i];
  }
}

Manager::Manager() :
  env( SDL_putenv(const_cast<char*>("SDL_VIDEO_CENTERED=center")) ),
  io( IOManager::getInstance() ),
  clock( Clock::getInstance() ),
  screen( io.getScreen() ),
  world("back", Gamedata::getInstance().getXmlInt("back/factor") ),
  viewport( Viewport::getInstance() ),
  sprites(),
  numberOfYellow(0),
  numberOfSmart(0),
  currentSprite(0)
{
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    throw string("Unable to initialize SDL: ");
  }
  atexit(SDL_Quit);
  sprites.push_back( new SubjectSprite("spinstar") );
  unsigned int n = Gamedata::getInstance().getXmlInt("numberOfStars");
  for (unsigned int i = 0; i < n; ++i) {
    sprites.push_back( new Sprite("star") );
  }
  numberOfYellow = Gamedata::getInstance().getXmlInt("numberOfOrbs");
  for (unsigned int i = 0; i < numberOfYellow; ++i) {
    sprites.push_back( new Sprite("orb") );
  }
  viewport.setObjectToTrack(sprites[currentSprite]);
}

void Manager::draw() const {
  world.draw();
  for (unsigned i = 0; i < sprites.size(); ++i) {
    sprites[i]->draw();
  }

  io.printMessageValueAt("Seconds: ", clock.getSeconds(), 10, 20);
  io.printMessageValueAt("fps: ", clock.getFps(), 10, 40);
  string message = "Strategy: " + Gamedata::getInstance().getStrategyString();
  io.printMessageAt(message, 10, 70);

  io.printMessageValueAt("Safe Distance: ", 
    SmartSprite::getSafeDistance(), 380, 20);
  static unsigned int seconds = 0;
  if ( clock.getSeconds() > seconds ) {
    seconds = clock.getSeconds();
  }
  unsigned noSprites = sprites.size();
  io.printMessageValueAt("Total sprites: ", noSprites, 380, 50);
  io.printMessageValueAt("Smart sprites: ", 
     std::min(noSprites, numberOfSmart), 380, 70);

  SDL_Flip(screen);
}

void Manager::checkForCollisions() {
  // sprites[0] is the spinning star:
  Sprite* player = static_cast<Sprite*>( sprites[0] );
  for (unsigned i = 1; i < sprites.size(); ++i) {
    Sprite* sprite = static_cast<Sprite*>( sprites[i] );
    ExplodingSprite* e = dynamic_cast<ExplodingSprite*>(sprite);
    if ( e && e->chunkCount() == 0 ) { 
      // Make a smart sprite
      SmartSprite* ss =
        new SmartSprite(sprite->getName(),sprite->getPosition(),
                        sprite->getFrame()->getWidth()/2, 
                        sprite->getFrame()->getHeight()/2);
      sprites[i] = ss;
      delete sprite;
      static_cast<SubjectSprite*>(sprites[0])->attach(ss);
      ++numberOfSmart;
    }
    else if ( !e && player->collidedWith(sprite) ) { 
      if ( dynamic_cast<SmartSprite*>(sprite) ) {
        static_cast<SubjectSprite*>(sprites[0])->
          detach(static_cast<SmartSprite*>(sprite) );
      }
      sprites[i] = new ExplodingSprite(sprite);
      delete sprite;
      if ( numberOfYellow ) --numberOfYellow;
    }
  }
}

void Manager::update() {
  ++clock;
  Uint32 ticks = clock.getElapsedTicks();
  for (unsigned int i = 0; i < sprites.size(); ++i) {
    sprites[i]->update(ticks);
  }
  checkForCollisions();
  world.update();
  viewport.update(); // always update viewport last
}

void Manager::play() {
  SDL_Event event;

  bool done = false;
  bool keyCatch = false;
  while ( not done ) {

    SDL_PollEvent(&event);
    Uint8 *keystate = SDL_GetKeyState(NULL);
    if (event.type ==  SDL_QUIT) { done = true; break; }
    if(event.type == SDL_KEYUP) { 
      keyCatch = false; 
    }
    if(event.type == SDL_KEYDOWN) {
      if (keystate[SDLK_ESCAPE] || keystate[SDLK_q]) {
        done = true;
        break;
      }
      if (keystate[SDLK_t] && !keyCatch) {
        keyCatch = true;
        currentSprite = (currentSprite+1) % sprites.size();
        viewport.setObjectToTrack(sprites[currentSprite]);
      }
      if (keystate[SDLK_p] && !keyCatch) {
        keyCatch = true;
        if ( clock.isPaused() ) clock.unpause();
        else clock.pause();
      }
      if (keystate[SDLK_s] && !keyCatch) {
        keyCatch = true;
        clock.toggleSloMo();
      }
      if (keystate[SDLK_p] && !keyCatch) {
        keyCatch = true;
        if ( clock.isPaused() ) clock.unpause();
        else clock.pause();
      }
      if (keystate[SDLK_PLUS] || keystate[SDLK_EQUALS]) { 
        if ( !keyCatch ) {
          keyCatch = true;
          SmartSprite::incrSafeDistance(); 
        }
      }
      if (keystate[SDLK_MINUS]) { 
        if ( !keyCatch ) {
          keyCatch = true;
          SmartSprite::decrSafeDistance();
        }
      }
    }

    draw();
    update();
  }
}
