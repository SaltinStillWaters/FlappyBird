#ifndef BIRD_H
#define BIRD_H

#include "DrawableObj.h"

class Bird : public DrawableObj {
public:
    Bird(GLenum drawMode, ArrayBuffer* vertices, bool normalized = true);
    Bird(GLenum drawMode, ArrayBuffer* vertices, IndexBuffer* indices, bool normalized = true);
    ~Bird();

    void update();
    void jump();

private:
    GLfloat rotateAngle = 0.f;
    GLfloat fly;
    bool isFlying;

    static constexpr GLfloat MAX_FLIGHT_HEIGHT = 1.85f;
    static constexpr GLfloat MIN_FLIGHT_HEIGHT = -0.95f;
    static constexpr GLfloat GRAVITY = 9.81f;
};

#endif
