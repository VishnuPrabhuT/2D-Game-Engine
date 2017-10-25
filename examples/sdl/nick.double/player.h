#ifndef PLAYER__H
#define PLAYER__H

#include "rotateSprite.h"

class Player : public rotateSprite {
public:
    Player(const std::string&);
    Player(const Player&);
    virtual void update(Uint32 ticks);

    Player& operator=(const Player&);

    void right();
    void left();
    void up();
    void down();
    void damp();

protected:
    void advanceFrame(Uint32 ticks);

private:
    float maxSpeed;
    float acceleration;
    float damping;
};

#endif
