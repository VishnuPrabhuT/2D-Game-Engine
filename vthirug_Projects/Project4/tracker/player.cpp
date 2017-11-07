#include "player.h"

Player::Player( const std::string& name) :
  TwoWayMultiSprite(name),
  collision(false),
  moving(false),
  initialVelocity(getVelocity())
{ }

Player::Player(const Player& s) :
  TwoWayMultiSprite(s), 
  collision(s.collision),
  moving(s.moving),
  initialVelocity(s.getVelocity())
  { }

Player& Player::operator=(const Player& s) {
  TwoWayMultiSprite::operator=(s);
  collision = s.collision;
  initialVelocity = s.initialVelocity;
  return *this;
}

void Player::stop() { 
  setVelocity(Vector2f(0,0));
}

void Player::right() { 
  images=runRight;
  if ( getX() < worldWidth-getScaledWidth()) {
    setVelocityX(initialVelocity[0]);
  }
} 
void Player::left()  { 
  images=runLeft;
  if ( getX() > 0) {
    setVelocityX(-initialVelocity[0]);
  }
} 
void Player::dash()  {
  if(images==runRight || images==idleRight){
    images=dashRight;
    if ( getY() > 0) {
      setVelocityX( initialVelocity[0]*(initialVelocity[0]*0.05) );
    }
  } 
  else if(images==runLeft || images==idleLeft){
    images=dashLeft;
    if ( getY() > 0) {
      setVelocityX( -initialVelocity[0]*(initialVelocity[0]*0.05) );
    }
  }
} 
void Player::down()  { 
  if ( getY() < worldHeight-getScaledHeight()) {
    setVelocityY( initialVelocity[1] );
  }
}

void Player::update(Uint32 ticks) {
  if ( !collision ) advanceFrame(ticks);  
  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  moving=incr[0]>0;  
  //Face right direction after stopping
  if(!moving){
    if(images==runRight || images==dashRight){
      images=idleRight;
    }
    if(images==runLeft || images==dashLeft){
      images=idleLeft;
    }
  }
  setPosition(getPosition() + incr);
  stop();
}

