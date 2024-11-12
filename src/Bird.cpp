#include "Bird.h"
#include "synchapi.h"

Bird::Bird(GLenum drawMode, ArrayBuffer* vertices)
    : DrawableObj(drawMode, vertices), rotate(0.f), yOffset(0.f), fly(0.f), isFlying(false) {}

Bird::Bird(GLenum drawMode, ArrayBuffer* vertices, IndexBuffer* indices)
    : DrawableObj(drawMode, vertices, indices), rotate(0.f), yOffset(0.f), fly(0.f), isFlying(false) {}

Bird::~Bird() {}

void Bird::update() {
    if (fly >= 0.35f) {
        isFlying = false;
        fly = 0;
    }

    if (isFlying) {
        if (yOffset < MAX_FLIGHT_HEIGHT - 1.0f) {
            rotate += rotate >= 45.f ? 0 : 4.f;
            yOffset += 0.001f * GRAVITY ;
        }
        fly += 0.01f;
    } else {
        if (yOffset > MIN_FLIGHT_HEIGHT) {
            rotate -= rotate <= -45.f ? 0 : 2.f;
            yOffset -= 0.002f * GRAVITY;
        }
    }
    Sleep(1000 / 60);
    setRotation(rotate);
    setOffset(-0.5f, yOffset);
}

void Bird::jump() {
    isFlying = true;
}
