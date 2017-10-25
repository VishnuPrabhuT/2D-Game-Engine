#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <random>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include "sprite.h"
#include "multisprite.h"
#include "rotateSprite.h"
#include "player.h"
#include "flock.h"
#include "gamedata.h"
#include "engine.h"
#include "frameGenerator.h"

Engine::~Engine() {
    delete glowship;
    for(Drawable *dr : behemoths) {
        delete dr;
    }
    for(Drawable *dr : darts) {
        delete dr;
    }
    std::cout << "Terminating program" << std::endl;
}

Engine::Engine() :
    rc( RenderContext::getInstance() ),
    io( IOmod::getInstance() ),
    clock( Clock::getInstance() ),
    renderer( rc->getRenderer() ),
    starfield("starfield", Gamedata::getInstance()
        .getXmlInt("starfield/factor") ),
    starfog("starfog", Gamedata::getInstance().getXmlInt("starfog/factor") ),
    starfront("starfront", Gamedata::getInstance()
        .getXmlInt("starfront/factor") ),
    viewport( Viewport::getInstance() ),
    birds("bird"),
    glowship(new Player("glowship")),
    currentSprite(0),
    makeVideo( false )
{
    for(int i = 0; i < Gamedata::getInstance().getXmlInt("dartCount"); i++) {
        //push some stars into the vector
        darts.push_back(new rotateSprite("dart"));
    }
    for(int i = 0; i < Gamedata::getInstance().getXmlInt("behemothCount"); i++) {
        //push some stars into the vector
        behemoths.push_back(new MultiSprite("behemoth"));
    }

    std::srand(std::time(0));

    for(Drawable *dr : darts) {
        //give each star a pseudorandom velocity
        dr->setVelocity(Vector2f(
            (std::rand()%200)+100, (std::rand()%200)+100));
    }

    glowship->setVelocity(Vector2f(
        (std::rand()%250)+100, (std::rand()%250)+100));

    Viewport::getInstance().setObjectToTrack(glowship);
    std::cout << "Loading complete" << std::endl;
}

void Engine::draw() const {
    starfield.draw();
    starfog.draw();
    starfront.draw();

    birds.draw();
    for(Drawable *dr : behemoths) {
        dr->draw();
    }
    for(Drawable *dr : darts) {
        dr->draw();
    }
    glowship->draw();

    viewport.draw();
    viewport.draw("FPS: "+std::to_string(clock.getFps()), 30, 60);
    SDL_RenderPresent(renderer);
}

void Engine::update(Uint32 ticks) {
    birds.update(ticks);
    for(Drawable *dr : behemoths) {
        dr->update(ticks);
    }
    for(Drawable *dr : darts) {
        dr->update(ticks);
    }
    glowship->update(ticks);
    starfront.update();
    starfog.update();
    starfield.update();
    viewport.update(); // always update viewport last
}

void Engine::switchSprite(){
    ++currentSprite;
    currentSprite = currentSprite % 4;
    if ( currentSprite == 0) {
        Viewport::getInstance().setObjectToTrack(glowship);
    }
    else if(currentSprite == 1) {
        Viewport::getInstance().setObjectToTrack(behemoths.front());
    }
    else if(currentSprite == 2) {
        Viewport::getInstance().setObjectToTrack(birds.flk.front());
    }
    else {
        Viewport::getInstance().setObjectToTrack(darts.front());
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
                if (keystate[SDL_SCANCODE_ESCAPE] || keystate[SDL_SCANCODE_Q])
                {
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
            if (keystate[SDL_SCANCODE_A]) {
                //down
                glowship->left();
            }
            if (keystate[SDL_SCANCODE_D]) {
                //down
                glowship->right();
            }
            if (keystate[SDL_SCANCODE_W]) {
                //down
                glowship->up();
            }
            if (keystate[SDL_SCANCODE_S]) {
                //down
                glowship->down();
            }
            draw();
            update(ticks);
            if ( makeVideo ) {
                frameGen.makeFrame();
            }
        }
    }
}
