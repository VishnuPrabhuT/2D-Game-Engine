#include "flock.h"
#include "gamedata.h"
#include <cstdlib>
#include <ctime>

flock::flock(const std::string &name) {
    //initialize the flock
    for(int i=0; i<Gamedata::getInstance().getXmlInt("birdCount"); i++)
    {
        //create a flock

        //make a bird
        rotateSprite *bird = new rotateSprite(name);

        //add some unpredictability to their starting velocities
        bird->setVelocityX(bird->getVelocityX() + (std::rand()%100) - 50);
        bird->setVelocityY(bird->getVelocityY() + (std::rand()%100) - 50);

        //add the bird to the flock
        flk.push_back(bird);
    }
}

void flock::draw() const {
    for(rotateSprite *brd : flk) {
        //draw each bird
        brd->draw();
    }
}

void flock::update(Uint32 ticks) {
    for(rotateSprite *brd : flk) {
        //update each bird
        steer(brd, (cohere(brd) + separate(brd) + avoid(brd)));
        brd->update(ticks);
    }
}

Vector2f flock::cohere(rotateSprite *brd) const {
    Vector2f heading(0, 0);
    int count = 0;
    int neighbor = Gamedata::getInstance().getXmlInt("birdNeighborRadius");

    for(rotateSprite *b : flk) {
        //for every bird in the flock

        //position from the nearest bird
        Vector2f dist = brd->getPosition() - b->getPosition();

        if(fabs(dist.magnitude()) < neighbor) {
            //a friend, flock up!

            heading -= dist;
            count++;
        }
    }

    if(count > 0) {
        heading /= count;

        heading /= Gamedata::getInstance().getXmlInt("flockCoherence");
    }

    return(heading);

}

Vector2f flock::align(rotateSprite *brd) const {
    Vector2f heading(0, 0);
    int count = 0;
    int neighbor = Gamedata::getInstance().getXmlInt("birdNeighborRadius");

    for(rotateSprite *b : flk) {
        //for every bird in the flock

        Vector2f dist = brd->getPosition() - b->getPosition();

        if(fabs(dist.magnitude()) < neighbor) {
            //a friend, fly with them!

            Vector2f adjust = b->getVelocity();
            heading += adjust;
            count++;
        }

    }
    if(count != 0) {
        heading /= count;

        heading /= Gamedata::getInstance().getXmlInt("flockAlignment");
    }

    return(heading);

}

Vector2f flock::separate(rotateSprite *brd) const {
    Vector2f heading(0, 0);
    int count = 0;
    int panic = Gamedata::getInstance().getXmlInt("birdPanicRadius");

    for(rotateSprite *b : flk) {
        //for every bird in the flock

        //position from nearest bird
        Vector2f dist = brd->getPosition() - b->getPosition();

        if(fabs(dist.magnitude()) < panic) {
            //too close!

            heading += dist;
            count++;
        }
    }

    if(count > 0) {
        heading /= count;

        heading /= Gamedata::getInstance().getXmlInt("flockSeparation");
    }
    return(heading);

}

Vector2f flock::avoid(rotateSprite *brd) const {
    int xPos = brd->getX();
    int yPos = brd->getY();
    int maxX = Gamedata::getInstance().getXmlInt("world/width");
    int maxY = Gamedata::getInstance().getXmlInt("world/height");
    int panic = Gamedata::getInstance().getXmlInt("birdPanicRadius");

    Vector2f heading(0, 0);
    if(xPos < panic) {
        //too close to the left
        Vector2f alter(panic-xPos, 0);
        heading += alter;
        heading.normalize();
    }
    if(yPos < panic) {
        //too close to the left
        Vector2f alter(0, panic-yPos);
        heading += alter;
        heading.normalize();
    }
    if(maxX - xPos < panic) {
        //too close to the left
        Vector2f alter(-panic-(maxX - xPos), 0);
        heading += alter;
        heading.normalize();
    }
    if(maxY - yPos < panic) {
        //too close to the left
        Vector2f alter(0, -panic-(maxY - yPos));
        heading += alter;
        heading.normalize();
    }


    heading /= Gamedata::getInstance().getXmlInt("flockAvoidance");

    return(heading);
}

void flock::steer(rotateSprite *brd, const Vector2f heading) {
    Vector2f speed = brd->getVelocity();
    int maxSpeed = Gamedata::getInstance().getXmlInt("birdMaxSpeed");

    brd->setVelocity(speed + heading);
    speed = brd->getVelocity();

    if(speed.magnitude() > maxSpeed) {
        //damp speed
        brd->setVelocity(speed /
            Gamedata::getInstance().getXmlFloat("birdDamping"));
    }

}
