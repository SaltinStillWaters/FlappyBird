#include "Bird.h"
#include "synchapi.h"

Bird::Bird(GLenum drawMode, ArrayBuffer* vertices, bool normalized)
    : DrawableObj(drawMode, vertices, nullptr), rotateAngle(0.f), fly(0.f), isFlying(false) {}

Bird::Bird(GLenum drawMode, ArrayBuffer* vertices, IndexBuffer* indices, bool normalized)
    : DrawableObj(drawMode, vertices, indices), rotateAngle(0.f), fly(0.f), isFlying(false) {}

Bird::~Bird() {}

void Bird::update() {
    if (fly >= 0.35f) {
        isFlying = false;
        fly = 0;
    }

    if (isFlying) {
        if (yOffset < MAX_FLIGHT_HEIGHT - 1.0f) {
            rotateAngle += rotateAngle >= 45.f ? 0 : 4.f;
            yOffset += 0.001f * GRAVITY ;
        }
        fly += 0.01f;
    } else {
        if (yOffset > MIN_FLIGHT_HEIGHT) {
            rotateAngle -= rotateAngle <= -45.f ? 0 : 2.f;
            yOffset -= 0.002f * GRAVITY;
        }
    }
    setRotation(rotateAngle);
    setOffset(-0.5f, yOffset);
}

void Bird::jump() {
    isFlying = true;
}
