#include "Bird.h"
#include <iostream>
#include <cmath>
#include "Pipes.h"
#include "GameController.h"

Bird::Bird(const std::string &birdFilename, GameController* controller) : controller(controller) {
    DrawableObj::type("bird", GL_QUADS, birdFilename, &DrawableObj::formatVertexColor);

    birdObj = DrawableObj::create("bird");

    GLfloat const scale = .12f;
    birdObj->setScale(scale);
    
    /*
        The bird sprite is a square with length = 1, centered at (0, 0).
        The hitbox is smaller than the bird; thus the emergence of 'reducedScale
    */
    GLfloat const reducedScale = scale - .03f;
    this->hitbox = new Hitbox(-.5f * reducedScale, .5f * reducedScale, -1.f * reducedScale, 1.f * reducedScale);
}

Bird::~Bird() {
    delete birdObj;
}

Hitbox* Bird::getHitbox() {
    return this->hitbox;
}

void Bird::update() {
    if (controller->getHasCollided()) { 
        //so the bird will continue to fall after collision
        if (birdObj->getYOffset() > -2) {
            ySpd = -maxYSpd / 2;
            birdObj->setOffset(0, birdObj->getYOffset() + ySpd);
        }
        return; 
    }

    if (ySpd > -maxYSpd) {
        ySpd += grav;
    }

    hitbox->updateY(ySpd);
    birdObj->setOffset(0, birdObj->getYOffset() + ySpd);
}

void Bird::jump() {
    if (controller->getHasCollided()) { return; }

    if (ySpd < maxYSpdToJump) {
        ySpd = jumpAcceleration;
    }
}

void Bird::draw() {
    birdObj->draw();
}