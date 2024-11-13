#ifndef BIRD_H
#define BIRD_H

#include "DrawableObj.h"

class Bird {
public:
    Bird(const std::string& birdFilename);
    ~Bird();

    void update();
    void jump();
    void draw();
    void setSize(GLfloat scale);

private:
    DrawableObj* birdObj;
    GLfloat rotateAngle = 0.f;
    GLfloat fly = 0.f;
    bool isFlying = false;
    GLfloat yOffset = 0.0f;

    static constexpr GLfloat MAX_FLIGHT_HEIGHT = 1.85f;
    static constexpr GLfloat MIN_FLIGHT_HEIGHT = -0.95f;
    static constexpr GLfloat GRAVITY = 9.81f;
    static constexpr GLfloat JUMP_INCREMENT = 0.01f;
};

#endif
