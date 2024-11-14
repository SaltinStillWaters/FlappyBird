#include "Hitbox.h"
#include <algorithm>
#include <iostream>

Hitbox::Hitbox(float xLeft, float xRight, float yBot, float yTop) {
    this->xLeft = xLeft;
    this->xRight = xRight;
    this->yBot = yBot;
    this->yTop = yTop;
}

bool Hitbox::checkCollision(const Hitbox& hitbox) const {
    // std::cout << "bird: (" << xLeft << ", " << xRight << ", " << yTop << ", " << yBot << ")\n"
    //           << "hitbox: (" << hitbox.xLeft << ", " << hitbox.xRight << ", " 
    //           << hitbox.yTop << ", " << hitbox.yBot << ")\n";
    return (checkXCollision(hitbox) && checkYCollision(hitbox));
}

void Hitbox::updateX(float offset) {
    xLeft += offset;
    xRight += offset;
}

void Hitbox::updateY(float offset) {
    yTop += offset;
    yBot += offset;
}

bool Hitbox::checkXCollision(const Hitbox& hitbox) const {
    return xLeft <= hitbox.xRight && xRight >= hitbox.xLeft;
}

bool Hitbox::checkYCollision(const Hitbox& hitbox) const {
    return yBot <= hitbox.yTop && yTop >= hitbox.yBot;
}

void Hitbox::printCoords() {
    std::cout << "x: " << xLeft << ", " << xRight << " y: " << yBot << ", " << yTop << '\n';
}