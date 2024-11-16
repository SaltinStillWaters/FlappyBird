#include "Bird.h"

#include "Pipes.h"
#include "GameController.h"

#include <iostream>
#include <cmath>

//static members
Bird* Bird::instance = nullptr;


Bird* Bird::getInstance(const std::string &birdFilename, GameController* controller) {
    if (instance == nullptr) {
        instance = new Bird(birdFilename, controller);
    }

    return instance;
}

Bird::Bird(const std::string &birdFilename, GameController* controller) : controller(controller) {
    DrawableObj::type("bird", GL_QUADS, birdFilename, &DrawableObj::formatVertexColor);
    birdObj = DrawableObj::create("bird");

    birdObj->setScale(Bird::BIRD_SCALE);
    
    this->hitbox = new Hitbox(-.5f * Bird::HITBOX_SCALE, .5f * Bird::HITBOX_SCALE,
                              -1.f * Bird::HITBOX_SCALE, 1.f * Bird::HITBOX_SCALE);
}

Bird::~Bird() { 
    delete birdObj; 
    delete hitbox;
}

Hitbox* Bird::getHitbox() { return hitbox; }

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

void Bird::reset() {
    ySpd = 0;
    angle = 0;

    hitbox->setXLeft(-0.5f * Bird::HITBOX_SCALE);
    hitbox->setXRight(0.5f * Bird::HITBOX_SCALE);
    hitbox->setYBot(-1.0f * Bird::HITBOX_SCALE);
    hitbox->setYTop(1.0f * Bird::HITBOX_SCALE);

    birdObj->setOffset(0, 0);
    birdObj->setRotation(0);
}