#include "Hitbox.h"
#include <algorithm>

Hitbox::Hitbox(float xLeft, float xRight, float yBot, float yTop) {
    this->xLeft = xLeft;
    this->xRight = xRight;
    this->yBot = yBot;
    this->yTop = yTop;
}

// void Hitbox::initPipeWidth() {
// //read from metadata
// }

void Hitbox::reshape(int width, int height) {
    float min = std::min(width, height);

    this->xLeft *= min/width;
    this->xRight *= min/width;

    this->yTop *= min/height;
    this->yBot *= min/height;
    
    //pipeWidth *= min/width;
}

bool Hitbox::checkCollision(const Hitbox& hitbox) {
    return (checkXCollision(hitbox) && checkYCollision(hitbox));
}

void Hitbox::updateX(float offset) {
    xLeft += offset;
    xRight += offset;
}

bool Hitbox::checkXCollision(const Hitbox& hitbox) {
    return (xLeft <= hitbox.xRight && xRight >= hitbox.xLeft) ||
           (hitbox.xLeft <= xRight && hitbox.xRight >= xLeft);
}

bool Hitbox::checkYCollision(const Hitbox& hitbox) {
    return (yBot <= hitbox.yTop && yTop >= hitbox.yBot) ||
           (hitbox.yBot <= yTop && hitbox.yTop >= yBot);
}