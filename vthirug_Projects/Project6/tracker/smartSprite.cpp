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
  safeDistance(Gamedata::getInstance().getXmlFloat(name+"/safeDistance")),
  bulletName( Gamedata::getInstance().getXmlStr(name+"/bullet") ),
  bulletsNPC(),
  freeBulletsNPC(),
  minSpeed( Gamedata::getInstance().getXmlInt(bulletName+"/speedX") ),
  bulletInterval(Gamedata::getInstance().getXmlInt(bulletName+"/interval")),
  timeSinceLastFrame(0)
{
  Bullet bullet(bulletName);
  freeBulletsNPC.push_back( bullet );
}


SmartSprite::SmartSprite(const SmartSprite& s) :
  TwoWayMultiSprite(s),
  playerPos(s.playerPos),
  playerWidth(s.playerWidth),
  playerHeight(s.playerHeight),
  currentMode(s.currentMode),
  safeDistance(s.safeDistance),
  bulletName(s.bulletName),
  bulletsNPC(s.bulletsNPC),
  freeBulletsNPC(s.freeBulletsNPC),
  minSpeed(s.minSpeed),
  bulletInterval(s.bulletInterval),
  timeSinceLastFrame(s.timeSinceLastFrame)
{}



void SmartSprite::explode() {

}


void SmartSprite::shoot() {
  std::cout << "out" << '\n';
  if ( timeSinceLastFrame < bulletInterval ) return;
  std::cout << "in" << '\n';
  float deltaX = getScaledWidth();
  float deltaY = getScaledHeight()/2;
  if (freeBulletsNPC.empty()) {
    Bullet bullet(bulletName);
    freeBulletsNPC.push_back( bullet );
    std::cout << "bullet" << '\n';
  }
  else {
    Bullet b = freeBulletsNPC.front();
    freeBulletsNPC.pop_front();
    b.reset();
    b.setPosition( getPosition() + Vector2f(deltaX/3, deltaY) );
    b.setVelocityY(-minSpeed*50);
    bulletsNPC.push_back( b );
  }
  timeSinceLastFrame = 0;
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

void SmartSprite::draw() const {
  TwoWayMultiSprite::draw();
  for ( const Bullet& freeBullet : bulletsNPC ) {
    if(!freeBullet.goneTooFar()){
      freeBullet.draw();
    }
  }
}

void SmartSprite::update(Uint32 ticks) {
  TwoWayMultiSprite::update(ticks);
  timeSinceLastFrame += ticks;

  std::list<Bullet>::iterator it=bulletsNPC.begin();
  while ( it != bulletsNPC.end() ) {
    if (!it->goneTooFar()){
      it->update( ticks );
      ++it;
    }
    else if ( !bulletsNPC.empty() ){
      Bullet b = bulletsNPC.front();
      it=bulletsNPC.erase(it);
      b.reset();
      freeBulletsNPC.push_back( b );
    }
  }

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
