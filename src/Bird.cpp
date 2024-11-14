#include "Bird.h"

#include "Pipes.h"
#include "GameController.h"

#include <iostream>
#include <cmath>

//static members
Bird* Bird::instance = nullptr;
std::mutex Bird::mtx;

Bird* Bird::getInstance(const std::string &birdFilename, GameController* controller) {
    if (instance == nullptr) {
        std::lock_guard<std::mutex> lock(mtx);
        if (instance == nullptr) {
            instance = new Bird(birdFilename, controller);
        }
    }

    return instance;
}

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
    if (!controller->getHasStarted()) { return; }

    if (controller->getHasCollided()) { 
        //so the bird will continue to fall after collision
        if (birdObj->getYOffset() > -2) {
            ySpd = -MAX_Y_SPD / 2;
            birdObj->setOffset(0, birdObj->getYOffset() + ySpd);
        }
        return; 
    }

    if (ySpd > -MAX_Y_SPD) {
        ySpd += GRAV;
    }

    hitbox->updateY(ySpd);
    birdObj->setOffset(0, birdObj->getYOffset() + ySpd);

    birdObj->setRotation(angle);
    
    //So the bird will stay at 45 degrees longer
    if (ySpd < MAX_Y_SPD_TO_JUMP && angle > MIN_ANGLE) {
        angle -= ANGULAR_SPD;
    }
}

void Bird::jump() {
    if (!controller->getHasStarted() || controller->getHasCollided()) { 
        return; 
    }

    if (ySpd < MAX_Y_SPD_TO_JUMP) {
        ySpd = JUMP_ACCELERATION;
        angle = MAX_ANGLE;
    }
}

void Bird::draw() {
    birdObj->draw();
}