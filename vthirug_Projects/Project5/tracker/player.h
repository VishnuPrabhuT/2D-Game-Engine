#ifndef PLAYER__H
#define PLAYER__H

#include <string>
#include <list>
#include <cmath>
#include <algorithm>
#include "twowaymultisprite.h"
#include "bullet.h"

class SmartSprite;

class Player : public TwoWayMultiSprite {
public:
  Player(const std::string&);
  Player(const Player&);
  virtual void update(Uint32 ticks);

  virtual void draw() const;
  void shoot();

  void collided() { collision = true; }
  void missed() { collision = false; }
  Player& operator=(const Player&);

  void right();
  void left();
  void dash();
  void roll();
  void stop();
  void attach( SmartSprite* o );
  void detach( SmartSprite* o );
private:
  std::list<SmartSprite*> observers;
  bool collision;
  bool moving;
  Vector2f initialVelocity;
  std::string bulletName;
  std::list<Bullet> bullets;
  std::list<Bullet> freeBullets;
  float minSpeed;
  float bulletInterval;
  float timeSinceLastFrame;
protected:
  //std::list<SmartSprite*> observers;
  //SubjectSprite& operator=(const SubjectSprite&);
};
#endif
