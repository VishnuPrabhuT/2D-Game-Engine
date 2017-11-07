#ifndef PLAYER__H
#define PLAYER__H

#include "twowaymultisprite.h"

class Player : public TwoWayMultiSprite {
public:
  Player(const std::string&);
  Player(const Player&);
  virtual void update(Uint32 ticks);

  void collided() { collision = true; }
  void missed() { collision = false; }
  Player& operator=(const Player&);

  void right();
  void left();
  void dash();
  void down();
  void stop();
private:
  bool collision;
  bool moving;
  Vector2f initialVelocity;
};
#endif