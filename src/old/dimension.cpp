#include "dimension.h"

Dimension::Dimension(float xLeft, float xRight, float yBot, float yTop) {
    this->xLeft = xLeft;
    this->xRight = xRight;
    this->yBot = yBot;
    this->yTop = yTop;
}

bool Dimension::checkCollision(const Dimension& dimension) {
    //std::cout << "Object: " << xLeft << " " << xRight << " " << yBot << " " << yTop << "\n\n";
    //std::cout << "Bird: " << dimension.xLeft << " " << dimension.xRight << " " << dimension.yBot << " " << dimension.yTop << "\n\n";

    return (checkXCollision(dimension) && checkYCollision(dimension));
}

void Dimension::updateX(float offset) {
    xLeft += offset;
    xRight += offset;
}

bool Dimension::checkXCollision(const Dimension& dimension) {
    return (xLeft <= dimension.xRight && xRight >= dimension.xLeft) ||
           (dimension.xLeft <= xRight && dimension.xRight >= xLeft);
}

bool Dimension::checkYCollision(const Dimension& dimension) {
    return (yBot <= dimension.yTop && yTop >= dimension.yBot) ||
           (dimension.yBot <= yTop && dimension.yTop >= yBot);
}