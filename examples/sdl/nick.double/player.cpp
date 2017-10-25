#include "player.h"
#include "gamedata.h"

Player::Player(const std::string &name) :
    rotateSprite(name)
{
    maxSpeed = Gamedata::getInstance().getXmlFloat("playerMaxSpeed");
    acceleration = Gamedata::getInstance().getXmlFloat("playerAcceleration");
    damping = Gamedata::getInstance().getXmlFloat("playerDamping");
}

Player::Player(const Player& p) :
    rotateSprite(p)
{
    maxSpeed = Gamedata::getInstance().getXmlFloat("playerMaxSpeed");
    acceleration = Gamedata::getInstance().getXmlFloat("playerAcceleration");
    damping = Gamedata::getInstance().getXmlFloat("playerDamping");
}

Player& Player::operator=(const Player& p) {
    rotateSprite::operator=(p);
    this->maxSpeed = p.maxSpeed;
    this->acceleration = p.acceleration;
    this->damping = p.damping;
    return *this;
}

void Player::advanceFrame(Uint32 ticks) {
	timeSinceLastFrame += ticks;
	if (timeSinceLastFrame > frameInterval) {
    currentFrame = (currentFrame+1) % numberOfFrames;
		timeSinceLastFrame = 0;
	}
}

void Player::left() {
    setVelocityX(getVelocityX() - acceleration);
}

void Player::right() {
    setVelocityX(getVelocityX() + acceleration);
}

void Player::up() {
    setVelocityY(getVelocityY() - acceleration);
}

void Player::down() {
    setVelocityY(getVelocityY() + acceleration);
}

void Player::damp() {
    float magnitude = getVelocity().magnitude();
    if(magnitude > maxSpeed) {
        //don't let player accelerate past max speed
        setVelocity(getVelocity().normalize() * maxSpeed);
    }
    else {
        if(magnitude > .01) {
            setVelocity(getVelocity() * damping);
        }
        else {
            setVelocity(getVelocity() * 0);
        }
    }
}

void Player::update(Uint32 ticks) {
    damp();
    rotateSprite::update(ticks);
    advanceFrame(ticks);
}
