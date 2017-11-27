#ifndef SMARTSPRITE__H
#define SMARTSPRITE__H
#include <string>
#include "twowaymultisprite.h"

class ExplodingSprite;

class SmartSprite : public TwoWayMultiSprite {
public:
  SmartSprite(const std::string&, const Vector2f& pos, int w, int h);
  SmartSprite(const std::string&, const Vector2f& pos, const Vector2f& vel,
         const Image*);
  SmartSprite(const SmartSprite&);
  virtual ~SmartSprite() { }

  virtual void explode();
  virtual void update(Uint32 ticks);
  void setPlayerPos(const Vector2f& p) { playerPos = p; }

private:
  enum LOOK {LEFT, RIGHT};
  Vector2f playerPos;
  int playerWidth;
  int playerHeight;
  LOOK currentMode;
  float safeDistance;

  void goLeft();
  void goRight();
  void goUp();
  void goDown();
};
#endif
