#include "Bird.h"
#include <iostream>
#include <cmath>

Bird::Bird(const std::string &birdFilename)
{
    DrawableObj::type("bird", GL_QUADS, birdFilename, &DrawableObj::formatVertexColor);

    birdObj = DrawableObj::create("bird");

    GLfloat const scale = .12f;
    birdObj->setScale(scale);
    
    /*
        The bird sprite is a square with length = 1, centered at (0, 0).
        The hitbox is smaller than the bird; thus the emergence of 'reducedScale
    */
    GLfloat const reducedScale = scale - .02f;
    this->hitbox = new Hitbox(-.5f * reducedScale, .5f * reducedScale, -1.f * reducedScale, 1.f * reducedScale);
}

Bird::~Bird()
{
    delete birdObj;
}

Hitbox* Bird::getHitbox() {
    return this->hitbox;
}

void Bird::update()
{
    //temp. Bird must be stopped by the GameController
    if (hitbox->yBot <= yMin ||
        hitbox->yTop >= yMax) {
            return;
    }
    
    if (std::fabs(ySpd) < std::fabs(maxYSpd)) {
        ySpd += grav;
    }

    hitbox->updateY(ySpd);
    birdObj->setOffset(0, birdObj->getYOffset() + ySpd);
    

}

void Bird::jump()
{
    if (ySpd < maxYSpdToJump) {
        ySpd = jumpAcceleration;
    }
}

void Bird::draw()
{
    birdObj->draw();
}