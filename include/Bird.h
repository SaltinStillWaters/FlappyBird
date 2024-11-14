#ifndef BIRD_H
#define BIRD_H

#include "DrawableObj.h"
#include "Hitbox.h"
#include "GameController.h"
class Bird {
public:
    Bird(const std::string& birdFilename, GameController* controller);
    ~Bird();

    void update();
    void jump();
    void draw();
    Hitbox* getHitbox();

private:
    GameController* controller;
    DrawableObj* birdObj;
    Hitbox* hitbox;
    GLfloat rotateAngle = 0.f;
    
    GLfloat maxYSpd = .2;
    GLfloat grav = -.001;
    GLfloat ySpd = 0;
    GLfloat maxYSpdToJump = 0;
    GLfloat jumpAcceleration = .035;
    GLfloat yMin = -1;
    GLfloat yMax = 1;
};

#endif
