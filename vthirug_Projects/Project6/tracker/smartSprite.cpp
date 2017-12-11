#include <cmath>
#include <random>
#include <functional>
#include "smartSprite.h"
#include "gamedata.h"
#include "renderContext.h"

#include <typeinfo>

float distance(float x1, float y1, float x2, float y2) {
  float x = x1-x2;
  float y = y1-y2;
  return hypot(x, y);
}

SmartSprite::SmartSprite(const std::string& name, const Vector2f& pos, int w, int h) :
  TwoWayMultiSprite(name),
  playerPos(pos),
  playerWidth(w),
  playerHeight(h),
  currentMode(RIGHT),
  safeDistance(Gamedata::getInstance().getXmlFloat(name+"/safeDistance"))
{}


SmartSprite::SmartSprite(const SmartSprite& s) :
  TwoWayMultiSprite(s),
  playerPos(s.playerPos),
  playerWidth(s.playerWidth),
  playerHeight(s.playerHeight),
  currentMode(s.currentMode),
  safeDistance(s.safeDistance)
{}

void SmartSprite::explode() {

}

void SmartSprite::goLeft()  {
  if (this->getName().find("Blue")!=std::string::npos) {
    images = blueMonsterLeft;
  }
  if (this->getName().find("Black")!=std::string::npos) {
    images = blackMonsterLeft;
  }
}
void SmartSprite::goRight()  {
  if (this->getName().find("Blue")!=std::string::npos) {
    images = blueMonsterRight;
  }
  if (this->getName().find("Black")!=std::string::npos) {
    images = blackMonsterRight;
  }
}
void SmartSprite::goUp()    { setVelocityY( -fabs(getVelocityY()) ); }
void SmartSprite::goDown()  { setVelocityY( fabs(getVelocityY()) );  }

void SmartSprite::update(Uint32 ticks) {
  TwoWayMultiSprite::update(ticks);
  float x= getX()+getImage()->getWidth()/2;
  float y= getY()+getImage()->getHeight()/2;
  float ex= playerPos[0]+playerWidth/2;
  float proximity=std::fabs(getPosition()[0]-ex);
  int ey= playerPos[1]+playerHeight/2;
  float distanceToEnemy = ::distance( x, y, ex, ey );
  if  ( currentMode == RIGHT ) {
    if(distanceToEnemy < safeDistance) currentMode = LEFT;
  }
  else if(currentMode == LEFT){
    if(distanceToEnemy > safeDistance) currentMode = RIGHT;
  }
  if ( proximity < safeDistance ){
    this->goLeft();
  }
  else{
    this->goRight();
  }
  if ( proximity > safeDistance ){
    this->goRight();
  }
  else{
    this->goLeft();
  }
  if ( y < ey ) goUp();
  if ( y > ey ) goDown();
}
