#include "Pipes.h"

#include <iostream>
#include <mutex>

//static members
Pipes* Pipes::instance = nullptr;
std::mutex Pipes::mtx;

unsigned int Pipes::updateCount = Pipes::updatesNeeded;


Pipes* Pipes::getInstance(GameController* controller, const Hitbox* birdHitbox, const std::string& topPipeFilename,
                         const std::string& botPipeFilename, const GLfloat xDisplacement, const GLfloat ySpace) {
    if (instance == nullptr) {
        std::lock_guard<std::mutex> lock(mtx);
        if (instance == nullptr) {
            instance = new Pipes(controller, birdHitbox, topPipeFilename, botPipeFilename, xDisplacement, ySpace);
        }
    }

    return instance;
}

Pipes::Pipes(GameController* controller, const Hitbox* birdHitbox, const std::string& topPipeFilename, 
             const std::string& botPipeFilename, const GLfloat xDisplacement, const GLfloat ySpace)
            : controller(controller), xDisplacement(xDisplacement), ySpace(ySpace), birdHitbox(birdHitbox) {
    DrawableObj::type("botPipe", GL_QUADS, botPipeFilename, &DrawableObj::formatVertexColor);
    DrawableObj::type("topPipe", GL_QUADS, topPipeFilename, &DrawableObj::formatVertexColor);

    randMt = new std::mt19937 { std::random_device{}() };
    distrib = new std::uniform_int_distribution<int> { 20, 80 };
}

Pipes::~Pipes() {
    int i = 0, j = 0;
    while(pipes.size() > 0) {
        std::cout << "Pipe cleanup " << ++i << '\n';
        delete pipes[0];
        delete pipes[1];
        pipes.pop_front();
        pipes.pop_front();
    }

    while (hitboxes.size() > 0) {
        std::cout << "Hitbox cleanup " << ++j << '\n';
        delete hitboxes[0];
        delete hitboxes[1];
        hitboxes.pop_front();
        hitboxes.pop_front();
    }
}

void Pipes::update() {
    createPipe();
    updatePipes();
    checkCollision();
}
void Pipes::createPipe() {
    if (!controller->getHasStarted() || controller->getHasCollided()) { 
        return; 
    }
    
    if (Pipes::updateCount < Pipes::updatesNeeded) {
        ++Pipes::updateCount;
        return;
    }
    Pipes::updateCount = 0;

    GLfloat yOffset = (*distrib)(*randMt) / 50.f;

    pipes.push_back(DrawableObj::create("botPipe"));
    pipes.back()->setOffset(1.f, yOffset - 2.f - (ySpace / 2.f));

    pipes.push_back(DrawableObj::create("topPipe"));
    pipes.back()->setOffset(1.f, yOffset + (ySpace / 2.f));

    //Upper and lower boundaries are +- 100, so the bird can not bypass the pipes
    //by going too high/low
    hitboxes.push_back(new Hitbox(1, 1 + this->pipeWidth, -100, yOffset - 1.f - (ySpace / 2.f)));
    hitboxes.push_back(new Hitbox(1, 1 + this->pipeWidth, yOffset - 1.f + (ySpace / 2.f), 100));
}

void Pipes::updatePipes() {
    if (!controller->getHasStarted() || controller->getHasCollided()) { 
        return; 
    }

    for (DrawableObj* obj : pipes) {
        obj->setOffset(obj->getXOffset() + this->xDisplacement, obj->getYOffset());
    }
    
    for (Hitbox* hitbox : hitboxes) {
        hitbox->updateX(this->xDisplacement);
    }

    if (pipes.size() >= 2 && pipes[0]->getXOffset() < -2.f - Pipes::pipeWidth) {
        delete pipes[0];
        delete pipes[1];
        pipes.pop_front();
        pipes.pop_front();
    }
}

void Pipes::checkCollision() {
    if (!controller->getHasStarted() || controller->getHasCollided()) { 
        return; 
    }

    //Y Boundaries Collision
    if (birdHitbox->yTop >= Pipes::Y_MAX ||
        birdHitbox->yBot <= Pipes::Y_MIN) {
        controller->setHasCollided();
        return;
    }

    //Pipe Collision
    if (hitboxes.size() < 2) {
        return;
    }

    if (birdHitbox->checkCollision(*hitboxes[0]) || birdHitbox->checkCollision(*hitboxes[1])) {
        controller->setHasCollided();
    }

    if (hitboxes[0]->xRight < birdHitbox->xLeft) {
        controller->addScore();

        delete hitboxes[0];
        delete hitboxes[1];
        hitboxes.pop_front();
        hitboxes.pop_front();
    }    
}

void Pipes::draw() {
    for (DrawableObj* obj : pipes) {
        obj->draw();
    }
}