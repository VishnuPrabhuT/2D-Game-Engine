#ifndef FLOCK__H
#define FLOCK__H

#include "rotateSprite.h"
#include "gamedata.h"

class flock {
public:
    //holds each bird for distance calculations
    std::vector<rotateSprite *> flk;

    //draws the birds one by one
    void draw() const;
    //manually sets each bird's position
    void update(Uint32 ticks);

    flock( const std::string &name);
    flock(const flock&) = delete;
    flock& operator=(const flock&) = delete;

    ~flock() {
        for(rotateSprite *brd : flk) {
            delete brd;
        }
    }
private:
    Vector2f cohere(rotateSprite *brd) const;
    Vector2f align(rotateSprite *brd) const;
    Vector2f separate(rotateSprite *brd) const;
    Vector2f avoid(rotateSprite *brd) const;
    void steer(rotateSprite *brd, const Vector2f heading);
};

#endif
