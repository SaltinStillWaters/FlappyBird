#ifndef BIRD_H
#define BIRD_H

#include "DrawableObj.h"

class Bird : public DrawableObj {
public:
    Bird(GLenum drawMode, ArrayBuffer* vertices);
    Bird(GLenum drawMode, ArrayBuffer* vertices, IndexBuffer* indices);
    ~Bird();

    void update();
    void jump();

private:
    GLfloat rotate;
    GLfloat yOffset;
    GLfloat fly;
    bool isFlying;

    static constexpr GLfloat MAX_FLIGHT_HEIGHT = 1.85f;
    static constexpr GLfloat MIN_FLIGHT_HEIGHT = -0.95f;
    static constexpr GLfloat GRAVITY = 9.81f;
};

#endif
