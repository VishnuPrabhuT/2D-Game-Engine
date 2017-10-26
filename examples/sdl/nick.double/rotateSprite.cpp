#include "rotateSprite.h"
#include "gamedata.h"
#include "multisprite.h"
#include "renderContext.h"

void rotateSprite::advanceFrame(Uint32 ticks) {
	timeSinceLastFrame += ticks;
	if (timeSinceLastFrame > frameInterval) {
    currentFrame = (currentFrame+1) % numberOfFrames;
		timeSinceLastFrame = 0;
	}
}

rotateSprite::rotateSprite( const std::string& name) :
    MultiSprite(name),
   	images( RenderContext::getInstance()->getImages(name) ),

   	currentFrame(0),
   	numberOfFrames( Gamedata::getInstance().getXmlInt(name+"/frames") ),
   	frameInterval( Gamedata::getInstance().getXmlInt(name+"/frameInterval")),
   	timeSinceLastFrame( 0 ),
   	worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
   	worldHeight(Gamedata::getInstance().getXmlInt("world/height"))
{ }

rotateSprite::rotateSprite(const rotateSprite& s) :
    MultiSprite(s),
    images(s.images),
    currentFrame(s.currentFrame),
    numberOfFrames( s.numberOfFrames ),
    frameInterval( s.frameInterval ),
    timeSinceLastFrame( s.timeSinceLastFrame ),
    worldWidth( s.worldWidth ),
    worldHeight( s.worldHeight )
{ }

rotateSprite& rotateSprite::operator=(const rotateSprite& s) {
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

void rotateSprite::draw() const {
  	images[currentFrame]->drawRotate(getX(), getY(), getScale(),
        getScaledWidth(), getScaledHeight(), getVelocityX(), getVelocityY());
}

void rotateSprite::update(Uint32 ticks) {
	MultiSprite::update(ticks);
  	advanceFrame(ticks); //doesn't get called in multisprite update

}
