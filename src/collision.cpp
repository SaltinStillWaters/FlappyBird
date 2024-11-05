#include "collision.h"


Collision::~Collision() {
    while (!pipes.empty()) {
        delete (pipes.front());
        pipes.pop_front();
    }
}

Collision::Collision(const float& PIPE_WIDTH, const float& X_START_LEFT, const float& Y_BOT_LIMIT, const float& Y_TOP_LIMIT)
                    : X_START_LEFT(X_START_LEFT), PIPE_WIDTH(PIPE_WIDTH), Y_BOT_LIMIT(Y_BOT_LIMIT), Y_TOP_LIMIT(Y_TOP_LIMIT) {}

void Collision::createPipe(float yLower, float ySpace) {
    Dimension* pipeBot = new Dimension(X_START_LEFT, X_START_LEFT + PIPE_WIDTH, Y_BOT_LIMIT, yLower);
    Dimension* pipeTop = new Dimension(X_START_LEFT, X_START_LEFT + PIPE_WIDTH, yLower + ySpace, Y_TOP_LIMIT);

    pipes.push_back(pipeBot);
    pipes.push_back(pipeTop);
}

void Collision::update(const Dimension& bird, const float offset) {
    for (int x = 0; x < pipes.size(); ++x) {
        pipes[x]->updateX(offset);
    }
    
    if (pipes.front()->xRight < bird.xLeft) {
        delete pipes[0];
        delete pipes[1];
        
        pipes.pop_front();
        pipes.pop_front();
    }
}

bool Collision::checkCollision(Dimension bird) {
    if (pipes.size() < 2) {
        return false;
    }

    return (bird.checkCollision(*pipes[0]) || bird.checkCollision(*pipes[1])
            || bird.yBot <= Y_BOT_LIMIT || bird.yTop >= Y_TOP_LIMIT);
}