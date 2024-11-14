#ifndef BIRD_H
#define BIRD_H

#include "DrawableObj.h"
#include "Hitbox.h"
#include "GameController.h"

#include <mutex>
/*
 To do:
 - Transform this into a singleton
 - Make necessary members constant
*/
class Bird {
public:
    ~Bird();
    Bird() = delete;
    Bird(const Bird& obj) = delete;
    
    static Bird* getInstance(const std::string &birdFilename, GameController* controller);

    void update();
    void jump();
    void draw();
    Hitbox* getHitbox();

private:
    GameController* controller;
    DrawableObj* birdObj;
    Hitbox* hitbox;
    
    GLfloat ySpd = 0;
    const GLfloat MAX_Y_SPD = .1;
    const GLfloat GRAV = -.002;
    const GLfloat MAX_Y_SPD_TO_JUMP = .02;
    const GLfloat JUMP_ACCELERATION = .045;

    GLfloat angle = 0;
    const GLfloat ANGULAR_SPD = 2;
    const GLfloat MAX_ANGLE = 45;
    const GLfloat MIN_ANGLE = -70;

    //Singleton
    static Bird* instance;
    static std::mutex mtx;
    Bird(const std::string &birdFilename, GameController* controller);
};

#endif
