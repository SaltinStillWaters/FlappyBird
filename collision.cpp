#include "collision.h"
#include <iostream>
#include <stdexcept>

// Dimension Constructor
Dimension::Dimension(float xLeft, float xRight, float yBot, float yTop) {
    this->xLeft = xLeft;
    this->xRight = xRight;
    this->yBot = yBot;
    this->yTop = yTop;
}

// Dimension Methods
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

// Collide Methods
Collide::~Collide() {
    while (!pipes.empty()) {
        delete (pipes.front());
        pipes.pop_front();
    }
}

void Collide::createPipe(float yLower, float ySpace) {
    Dimension* pipeBot = new Dimension(X_START_LEFT, X_START_LEFT + PIPE_WIDTH, Y_BOT_LIMIT, yLower);
    Dimension* pipeTop = new Dimension(X_START_LEFT, X_START_LEFT + PIPE_WIDTH, yLower + ySpace, Y_TOP_LIMIT);

    pipes.push_back(pipeBot);
    pipes.push_back(pipeTop);
}

void Collide::update(const Dimension& bird) {
    for (int x = 0; x < pipes.size(); ++x) {
        pipes[x]->updateX(-0.01f);
    }
    
    if (pipes.front()->xRight < bird.xLeft) {
        delete pipes[0];
        delete pipes[1];
        
        pipes.pop_front();
        pipes.pop_front();
    }
}

bool Collide::checkCollision(Dimension bird) {
    if (pipes.size() < 2) {
        return false;
    }

    return (bird.checkCollision(*pipes[0]) || bird.checkCollision(*pipes[1]));
}