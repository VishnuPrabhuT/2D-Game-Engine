#ifndef TWOWAYMULTISPRITE__H
#define TWOWAYMULTISPRITE__H
#include <string>
#include <vector>
#include <cmath>
#include <string>
#include "drawable.h"

class TwoWayMultiSprite : public Drawable {
public:
  TwoWayMultiSprite(const std::string&);

  virtual void draw() const;
  virtual void update(Uint32 ticks);

  virtual const Image* getImage() const {
    return images[currentFrame];
  }
  int getScaledWidth()  const {
    return getScale()*images[currentFrame]->getWidth();
  }
  int getScaledHeight()  const {
    return getScale()*images[currentFrame]->getHeight();
  }
  virtual const SDL_Surface* getSurface() const {
    return images[currentFrame]->getSurface();
  }

protected:
  std::vector<Image *> idleRight;
  std::vector<Image *> idleLeft;
  std::vector<Image *> runRight;
  std::vector<Image *> runLeft;
  std::vector<Image *> dashRight;
  std::vector<Image *> dashLeft;
  std::vector<Image *> blueMonsterLeft;
  std::vector<Image *> blueMonsterRight;
  std::vector<Image *> images;


  unsigned currentFrame;
  unsigned numberOfFrames;
  unsigned frameInterval;
  float timeSinceLastFrame;
  int worldWidth;
  int worldHeight;

  void advanceFrame(Uint32 ticks);
  TwoWayMultiSprite(const TwoWayMultiSprite&);
  TwoWayMultiSprite& operator=(const TwoWayMultiSprite&);
};
#endif
