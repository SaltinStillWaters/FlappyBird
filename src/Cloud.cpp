#include "Cloud.h"

#include <iostream>

//static members
Cloud* Cloud::instance = nullptr;
unsigned int Cloud::updateCount = Cloud::updatesNeeded;

Cloud* Cloud::getInstance(const std::string& cloudFilename, 
                          const GLfloat xDisplacement,
                          const GLfloat ySpace) {
    return instance;


    if (instance == nullptr) {
        instance = new Cloud(cloudFilename, xDisplacement, ySpace);
    }
    return instance;
}

Cloud::Cloud(const std::string& cloudFilename,
             const GLfloat xDisplacement,
             const GLfloat ySpace)
            : xDisplacement(xDisplacement), ySpace(ySpace) {
    DrawableObj::type("cloud", GL_QUADS, cloudFilename, &DrawableObj::formatVertexColor);

    randMt = new std::mt19937 { std::random_device{}() };
    distrib = new std::uniform_int_distribution<int> { 20, 80 };
}

Cloud::~Cloud() {
    int i = 0, j = 0;
    while(clouds.size() > 0) {
        std::cout << "Cloud cleanup " << ++i << '\n';
        delete clouds[0];
        clouds.pop_front();
    }

    delete randMt;
    delete distrib;
}

void Cloud::update() {
    createCloud();
    updateCloud();
}

void Cloud::createCloud() {
    if (Cloud::updateCount < Cloud::updatesNeeded) {
        ++Cloud::updateCount;
        return;
    }
    Cloud::updateCount = 0;

    GLfloat yOffset = (*distrib)(*randMt) / 50.f;

    clouds.push_back(DrawableObj::create("cloud"));
    clouds.back()->setOffset(1.f, yOffset - 2.f - (ySpace / 2.f));
}

void Cloud::updateCloud() {
    for (DrawableObj* obj : clouds) {
        obj->setOffset(obj->getXOffset() + this->xDisplacement, obj->getYOffset());
    }

    if (clouds.size() >= 2 && clouds[0]->getXOffset() < -2.f - Cloud::cloudWidth) {
        delete clouds[0];
        delete clouds[1];
        clouds.pop_front();
        clouds.pop_front();
    }
}

void Cloud::draw() {
    for (DrawableObj* obj : clouds) {
        obj->draw();
        obj->setScale(.005f);
    }
}

void Cloud::reset() {
    while(clouds.size() > 0) {
        delete clouds[0];
        clouds.pop_front();
    }

    Cloud::updateCount = Cloud::updatesNeeded;
}