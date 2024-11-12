#include "Pipes.h"
#include <iostream>

unsigned int Pipes::updateCount = Pipes::updatesNeeded;

Pipes::Pipes(const std::string& topPipeFilename, const std::string& botPipeFilename, const GLfloat xDisplacement, const GLfloat ySpace)
    : xDisplacement(xDisplacement), ySpace(ySpace) {
    DrawableObj::type("botPipe", GL_QUADS, botPipeFilename, &DrawableObj::formatVertexColor);
    DrawableObj::type("topPipe", GL_QUADS, topPipeFilename, &DrawableObj::formatVertexColor);

    randMt = new std::mt19937 { std::random_device{}() };
    distrib = new std::uniform_int_distribution<int> { 20, 80 };
}

void Pipes::createPipe() {
    if (Pipes::updateCount < updatesNeeded) {
        ++Pipes::updateCount;
        return;
    }
    Pipes::updateCount = 0;

    GLfloat yOffset = (*distrib)(*randMt) / 50.f;

    pipes.push_back(DrawableObj::create("botPipe"));
    pipes.back()->setOffset(0, yOffset - 2 - ySpace / 2);

    pipes.push_back(DrawableObj::create("topPipe"));
    pipes.back()->setOffset(0, yOffset + ySpace / 2);

    hitboxes.push_back(new Hitbox(1, 1 + this->pipeWidth, -1, ySpace / 2 + yOffset - 1));
    hitboxes.push_back(new Hitbox(1, 1 + this->pipeWidth, ySpace / 2 + yOffset - 1, 1));
}

void Pipes::updatePipes() {
    for (DrawableObj* obj : pipes) {
        obj->setOffset(obj->getXOffset() + this->xDisplacement, obj->getYOffset());
    }
    
    for (Hitbox* hitbox : hitboxes) {
        hitbox->updateX(this->xDisplacement);
    }

    if (pipes.size() >= 2 && pipes[0]->getXOffset() < -2.f - this->pipeWidth) {
        std::cout << "Pipe Deleted: ";
        delete pipes[0];
        delete pipes[1];
        pipes.pop_front();
        pipes.pop_front();
    }
}

bool Pipes::checkCollision() {
    if (hitboxes.size() < 2) {
        return false;
    }

    if (hitboxes[0]->xRight < birdHitbox->xLeft) {
        std::cout << "Hitbox deleted\n";
        delete hitboxes[0];
        delete hitboxes[1];
        hitboxes.pop_front();
        hitboxes.pop_front();
    }

    if (birdHitbox->checkCollision(*hitboxes[0]) || birdHitbox->checkCollision(*hitboxes[1])) {
        //std::cout << "COLLISION!!!\n";
    }

    return (birdHitbox->checkCollision(*hitboxes[0]) || birdHitbox->checkCollision(*hitboxes[1]));
}

void Pipes::draw() {
    for (DrawableObj* obj : pipes) {
        obj->draw();
    }
}