#ifndef BIRD_H
#define BIRD_H

#include "Resettable.h"
#include "DrawableObj.h"
#include "Hitbox.h"
#include "GameController.h"

class Bird : public Resettable {
public:
    void update();
    void jump();
    void draw();

    Hitbox* getHitbox();

    void reset() override;

    //Singleton
    ~Bird();
    Bird() = delete;
    Bird(const Bird& obj) = delete;
    
    static Bird* getInstance(const std::string &birdFilename, GameController* controller);
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

    static GLfloat constexpr BIRD_SCALE = .12f;
    static GLfloat constexpr HITBOX_SCALE = BIRD_SCALE - .03f;

    //Singleton
    static Bird* instance;
    Bird(const std::string &birdFilename, GameController* controller);
};

#endif
