#include "twowaymultisprite.h"
#include "gamedata.h"
#include "renderContext.h"

void TwoWayMultiSprite::advanceFrame(Uint32 ticks) {
	timeSinceLastFrame += ticks;
	if (timeSinceLastFrame > frameInterval) {
    currentFrame = (currentFrame+1) % numberOfFrames;
		timeSinceLastFrame = 0;
	}
}

TwoWayMultiSprite::TwoWayMultiSprite( const std::string& name) :
  Drawable(name,
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"),
                    Gamedata::getInstance().getXmlInt(name+"/startLoc/y")),
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/speedX"),
                    Gamedata::getInstance().getXmlInt(name+"/speedY"))
           ),
  idleRight( RenderContext::getInstance()->getImages(name) ),
  idleLeft( RenderContext::getInstance()->getImages("IdleLeft") ),
  runRight( RenderContext::getInstance()->getImages("RunRight") ),
  runLeft( RenderContext::getInstance()->getImages("RunLeft") ),
  dashRight( RenderContext::getInstance()->getImages("DashRight") ),
  dashLeft( RenderContext::getInstance()->getImages("DashLeft") ),
  rollRight( RenderContext::getInstance()->getImages("RollRight") ),
	blueMonsterLeft( RenderContext::getInstance()->getImages("BlueMonsterLeft") ),
	blueMonsterRight( RenderContext::getInstance()->getImages("BlueMonsterRight") ),
	blackMonsterLeft( RenderContext::getInstance()->getImages("BlackMonsterLeft") ),
	blackMonsterRight( RenderContext::getInstance()->getImages("BlackMonsterRight") ),
  images(idleRight),
  currentFrame(0),
  numberOfFrames( Gamedata::getInstance().getXmlInt(name+"/frames") ),
  frameInterval( Gamedata::getInstance().getXmlInt(name+"/frameInterval")),
  timeSinceLastFrame( 0 ),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height"))
{ }

TwoWayMultiSprite::TwoWayMultiSprite(const TwoWayMultiSprite& s) :
  Drawable(s),
	idleRight(s.idleRight),
	idleLeft(s.idleLeft),
	runRight(s.runRight),
	runLeft(s.runLeft),
	dashRight(s.dashRight),
	dashLeft(s.dashLeft),
  rollRight(s.rollRight),
	blueMonsterLeft(s.blueMonsterLeft),
	blueMonsterRight(s.blueMonsterRight),
  images(s.images),
  currentFrame(s.currentFrame),
  numberOfFrames( s.numberOfFrames ),
  frameInterval( s.frameInterval ),
  timeSinceLastFrame( s.timeSinceLastFrame ),
  worldWidth( s.worldWidth ),
  worldHeight( s.worldHeight )
  { }

TwoWayMultiSprite& TwoWayMultiSprite::operator=(const TwoWayMultiSprite& s) {
  Drawable::operator=(s);
  images = (s.images);
  currentFrame = (s.currentFrame);
  numberOfFrames = ( s.numberOfFrames );
  frameInterval = ( s.frameInterval );
  timeSinceLastFrame = ( s.timeSinceLastFrame );
  worldWidth = ( s.worldWidth );
  worldHeight = ( s.worldHeight );
  return *this;
}

void TwoWayMultiSprite::draw() const {
	images[currentFrame]->draw(getX(), getY(), getScale());
}

void TwoWayMultiSprite::update(Uint32 ticks) {
  advanceFrame(ticks);

  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);

  if ( getY() < 0) {
    setVelocityY( fabs( getVelocityY() ) );
  }
  if ( getY() > worldHeight-getScaledHeight()) {
    setVelocityY( -fabs( getVelocityY() ) );
  }

  if ( getX() < 0) {
    setVelocityX( fabs( getVelocityX() ) );
    //images=idleRight;
  }
  if ( getX() > worldWidth-getScaledWidth()) {
    setVelocityX( -fabs( getVelocityX() ) );
    //images=idleLeft;
  }

}
