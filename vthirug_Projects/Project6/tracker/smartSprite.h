#ifndef SMARTSPRITE__H
#define SMARTSPRITE__H
#include <string>
#include <list>
#include <cmath>
#include <algorithm>
#include "twowaymultisprite.h"
#include "bullet.h"
#include "clock.h"
#include "engine.h"

class ExplodingSprite;

class SmartSprite : public TwoWayMultiSprite {
public:
  SmartSprite(const std::string&, const Vector2f& pos, int w, int h);
  SmartSprite(const std::string&, const Vector2f& pos, const Vector2f& vel,
         const Image*);
  SmartSprite(const SmartSprite&);
  virtual ~SmartSprite() { }

  virtual void shoot();
  virtual void explode();
  virtual void draw() const;
  virtual void update(Uint32 ticks);
  void setPlayerPos(const Vector2f& p) { playerPos = p; }
  std::list<Bullet>& getBulletList(){ return bulletsNPC; }
private:
  enum LOOK {LEFT, RIGHT};
  Vector2f playerPos;
  int playerWidth;
  int playerHeight;
  LOOK currentMode;
  float safeDistance;
  std::string bulletName;
  std::list<Bullet> bulletsNPC;
  std::list<Bullet> freeBulletsNPC;
  float minSpeed;
  float bulletInterval;
  float timeSinceLastFrame;

  void goLeft();
  void goRight();
  void goUp();
  void goDown();
};
#endif
