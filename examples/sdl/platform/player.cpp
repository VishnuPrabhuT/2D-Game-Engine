#include <iostream>
#include <cmath>
#include "player.h"
#include "gamedata.h"
#include "imageFactory.h"

constexpr float fGravity = 100.0f;
constexpr float fJumpImpulse = -200.0f;

void Player::advanceFrame(Uint32 ticks) {
	timeSinceLastImage += ticks;
	if (timeSinceLastImage > frameInterval) {
    currentFrame = (currentFrame+1) % numberOfFrames;
		timeSinceLastImage = 0;
	}
}

Player::Player( const std::string& name) :
  Drawable(name, 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"), 
                    Gamedata::getInstance().getXmlInt(name+"/startLoc/y")), 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/speed/x"),
                    Gamedata::getInstance().getXmlInt(name+"/speed/y"))
           ),
  imagesLeft( ImageFactory::getInstance().getImages(name+"Left") ),
  imagesRight( ImageFactory::getInstance().getImages(name) ),
  images(imagesRight),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  restingContact(true),

  initialVelocity(getVelocity()),
  currentFrame(0),
  numberOfFrames( Gamedata::getInstance().getXmlInt(name+"/frames") ),
  frameInterval( Gamedata::getInstance().getXmlInt(name+"/frameInterval") ),
  timeSinceLastImage(0),

  facing(RIGHT)
{ }

Player::
Player(const Player& s) :
  Drawable(s.getName(), s.getPosition(), s.getVelocity()),
  imagesLeft(s.imagesLeft),
  imagesRight(s.imagesRight),
  images(s.imagesRight),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  restingContact(true),

  initialVelocity(s.initialVelocity),
  currentFrame(s.currentFrame),
  numberOfFrames( s.numberOfFrames ),
  frameInterval( s.frameInterval ),
  timeSinceLastImage( s.timeSinceLastImage ),

  facing(RIGHT)
{ }

void Player::stop() { 
  setVelocity( Vector2f(0, 0) );
}

void Player::jump() { 
  if(restingContact)
  {
    setVelocityY(fJumpImpulse);
    restingContact = false;
  }
} 

void Player::right() { 
  if ( getX() < worldWidth-getScaledWidth() && restingContact ) {
    setVelocityX(initialVelocity[0]);
  }
} 
void Player::left()  { 
  if ( getX() > 0 && restingContact ) {
    setVelocityX(-initialVelocity[0]);
  }
} 
void Player::up()    { 
  if ( getY() > 0) {
    setVelocityY( -initialVelocity[1] );
  }
} 
void Player::down()  { 
  if ( getY() < worldHeight-getScaledHeight()) {
    setVelocityY( initialVelocity[1] );
  }
}

void Player::draw() const { 
  Uint32 x = static_cast<Uint32>(getX());
  Uint32 y = static_cast<Uint32>(getY());
  images[currentFrame]->draw(x, y);
}

void Player::update(Uint32 ticks) { 
  if(restingContact)
  {
    if (getVelocity() != Vector2f(0, 0) ) advanceFrame(ticks);
  }
  else
  {
    setVelocityY(getVelocityY() + static_cast<float>(ticks) * fGravity * 0.001f);
  }

  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);

  if ( getY() > worldHeight - getScaledHeight() && getVelocityY() > 0.0f) {
    restingContact = true;
    setY(worldHeight - getScaledHeight());
  }
  if ( getX() < 0) {
    setVelocityX(0.0f);
    setX(0.0f);
  }
  if ( getX() > worldWidth-getScaledWidth()) {
    setVelocityX(0.0f);
    setX(worldWidth-getScaledWidth());
  }  
  if ( getVelocityX() > 0 ) {
    images = imagesRight;
    facing = RIGHT;
  }
  else if ( getVelocityX() < 0 ) {
    images = imagesLeft;
    facing = LEFT;
  }
  else {
    if ( facing  == LEFT ) images = imagesLeft;
    else images = imagesRight;
  }

  if(restingContact)
  {
    setVelocityY(std::max(getVelocityY(), 0.0f));
    stop();
  }
}
