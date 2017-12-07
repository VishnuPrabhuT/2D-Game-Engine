#ifndef PLAYER__H
#define PLAYER__H

#include <string>
#include <iostream>
#include <vector>
#include "drawable.h"

class Player : public Drawable {
public:
  Player(const std::string&);
  Player(const Player& s);
  virtual ~Player() { } 
  virtual const Image* getImage() const { return images[currentFrame]; }

  int getScaledWidth()  const { 
    return getScale()*images[currentFrame]->getWidth(); 
  } 
  int getScaledHeight()  const { 
    return getScale()*images[currentFrame]->getHeight(); 
  } 
  virtual const SDL_Surface* getSurface() const { 
    return images[currentFrame]->getSurface();
  }


  virtual void draw() const;
  virtual void update(Uint32 ticks);

  void jump();
  void right();
  void left();
  void up();
  void down();
  void stop();

  Player& operator=(const Player&) = delete;
private:
  const std::vector<Image *> imagesLeft;
  const std::vector<Image *> imagesRight;
        std::vector<Image *> images;

  int worldWidth;
  int worldHeight;

  bool restingContact;

  Vector2f initialVelocity;

  // Data attributes to manage frames:
  unsigned currentFrame;
  unsigned numberOfFrames;
  unsigned frameInterval;
  float timeSinceLastImage;

  enum FACE { LEFT, RIGHT };
  FACE facing;

  void advanceFrame(Uint32 ticks);
  virtual void incrFrame() { 
    currentFrame = (currentFrame+1) % numberOfFrames;
  }

};
#endif
