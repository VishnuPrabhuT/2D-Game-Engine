#ifndef ROTATESPRITE__H
#define ROTATESPRITE__H

#include "multisprite.h"

class rotateSprite : public MultiSprite {
public:
    rotateSprite(const std::string&);
    rotateSprite(const rotateSprite&);

    virtual void draw() const;
    virtual void update(Uint32 ticks);

protected:
    std::vector<Image *> images;

    unsigned currentFrame;
    unsigned numberOfFrames;
    unsigned frameInterval;
    float timeSinceLastFrame;
    int worldWidth;
    int worldHeight;

    void advanceFrame(Uint32 ticks);
    rotateSprite& operator=(const rotateSprite&);
};

#endif
