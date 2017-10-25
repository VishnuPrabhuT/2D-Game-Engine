#ifndef ENGINE__H
#define ENGINE__H

#include <vector>
#include <SDL.h>
#include "ioMod.h"
#include "renderContext.h"
#include "clock.h"
#include "world.h"
#include "viewport.h"
#include "flock.h"
#include "player.h"

class Engine {
public:
    Engine ();                            //allow only default constructor
    Engine(const Engine&) = delete;
    Engine& operator=(const Engine&) = delete;
    ~Engine ();                           //destructor
    void play();
    void switchSprite();

private:
    const RenderContext* rc;
    const IOmod& io;
    Clock& clock;

    SDL_Renderer * const renderer;
    World starfield;
    World starfog;
    World starfront;
    Viewport& viewport;

    flock birds;
    std::vector<Drawable*> behemoths;
    Player* glowship;
    std::vector<Drawable*> darts;
    int currentSprite;

    bool makeVideo;

    void draw() const;
    void update(Uint32);

    void printScales() const;
    void checkForCollisions();
};

#endif
