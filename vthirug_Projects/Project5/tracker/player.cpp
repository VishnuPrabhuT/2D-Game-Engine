#include "player.h"
#include "smartSprite.h"
#include "gamedata.h"
#include "renderContext.h"

/*Player::~Player() {
  for (auto bullet : bullets) {
    delete bullet;
  }

  for (auto bullet : freeBullets) {
    delete bullet;
  }
}*/

Player::Player( const std::string& name) :
  TwoWayMultiSprite(name),
  observers(),
  collision(false),
  moving(false),
  initialVelocity(getVelocity()),
  bulletName( Gamedata::getInstance().getXmlStr(name+"/bullet") ),
  bullets(),
  freeBullets(),
  minSpeed( Gamedata::getInstance().getXmlInt(bulletName+"/speedX") ),
  bulletInterval(Gamedata::getInstance().getXmlInt(bulletName+"/interval")),
  timeSinceLastFrame(0)
{
  Bullet bullet(bulletName);
  freeBullets.push_back( bullet );
}

Player::Player(const Player& s) :
  TwoWayMultiSprite(s),
  observers(s.observers),
  collision(s.collision),
  moving(s.moving),
  initialVelocity(s.getVelocity()),
  bulletName(s.bulletName),
  bullets(s.bullets),
  freeBullets(s.freeBullets),
  minSpeed(s.minSpeed),
  bulletInterval(s.bulletInterval),
  timeSinceLastFrame(s.timeSinceLastFrame)
  { }

Player& Player::operator=(const Player& s) {
  TwoWayMultiSprite::operator=(s);
  collision = s.collision;
  initialVelocity = s.initialVelocity;
  return *this;
}

void Player::shoot() {
  if ( timeSinceLastFrame < bulletInterval ) return;
  float deltaX = getScaledWidth();
  float deltaY = getScaledHeight()/2;
  // I need to add some minSpeed to velocity:

  if (freeBullets.empty()) {
    Bullet bullet(bulletName);
    freeBullets.push_back( bullet );
  }
  else {
    Bullet b = freeBullets.front();
    freeBullets.pop_front();
    b.reset();
    //std::cout << this->getName() << '\n';
    if(images == runRight || images == idleRight || images == dashRight) {
      b.setPosition( getPosition() + Vector2f(deltaX, deltaY) );
      b.setVelocity( 2*(getVelocity() + Vector2f(minSpeed, 0)));
    }
    else {
      b.setPosition( getPosition() + Vector2f(deltaX-150, deltaY) );
      b.setVelocity((-2)*(-getVelocity() + Vector2f(minSpeed, 0)));
    }
    bullets.push_back( b );
  }
  timeSinceLastFrame = 0;
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
void Player::roll()  {
  images=rollRight;
  if ( getY() < worldHeight-getScaledHeight()) {
    setVelocityX( initialVelocity[0] );
  }
}

void Player::attach( SmartSprite* o ) {
  observers.push_back(o);
}

void Player::detach( SmartSprite* o ) {
  std::list<SmartSprite*>::iterator ptr = observers.begin();
  while ( ptr != observers.end() ) {
    if ( *ptr == o ) {
      ptr = observers.erase(ptr);
      return;
    }
    ++ptr;
  }
}

void Player::draw() const {
  TwoWayMultiSprite::draw();
  for ( const Bullet& freeBullet : bullets ) {
    if(!freeBullet.goneTooFar()){
      freeBullet.draw();
    }
  }
}

void Player::update(Uint32 ticks) {
  if ( !collision ) advanceFrame(ticks);
  timeSinceLastFrame += ticks;
  TwoWayMultiSprite::update(ticks);
  //Sprite::update(ticks);
  std::list<Bullet>::iterator it=bullets.begin();
  while ( it != bullets.end() ) {
    if (!it->goneTooFar()){
      it->update( ticks );
      //std::cout << freeBullets.size() << "\n" << bullets.size() << '\n';
      ++it;
    }
    else if ( !bullets.empty() ){
      Bullet b = bullets.front();
      it=bullets.erase(it);
      b.reset();
      freeBullets.push_back( b );
    }
  }
  /*for ( Bullet& freeBullet : bullets ) {
    if (!freeBullet.goneTooFar()){
      freeBullet.update( ticks );
      std::cout << freeBullets.size()<<"\n"<<bullets.size() << '\n';
    }
    else if (freeBullet.goneTooFar()){
      freeBullet.reset();
      freeBullets.push_back(freeBullet);
      bullets.pop_front();
    }*/

  std::list<SmartSprite*>::iterator ptr = observers.begin();
  while ( ptr != observers.end() ) {
    (*ptr)->setPlayerPos( getPosition() );
    ++ptr;
  }
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
