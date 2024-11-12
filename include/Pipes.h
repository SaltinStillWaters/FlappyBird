#ifndef PIPES_H
#define PIPES_H

#include "DrawableObj.h"
#include "Hitbox.h"
#include "ArrayBuffer.h"
#include <deque>
#include <string>
#include <random>

/*
To Do
add birdHitbox to constructor
*/
class Pipes {
private:
    std::deque<DrawableObj*> pipes;
    std::deque<Hitbox*> hitboxes;

    const Hitbox* birdHitbox = new Hitbox(-0.5, 0, -0.5, 0.5);

    ArrayBuffer* topPipeVBO;
    ArrayBuffer* botPipeVBO;
    const GLfloat xDisplacement;
    const GLfloat ySpace;
    const float pipeWidth = .33814; //temp

    static const unsigned int updatesNeeded = 120; //change this as needed
    static unsigned int updateCount;
    
    std::mt19937* randMt;
    std::uniform_int_distribution<int>* distrib;

public:
    Pipes(const std::string& topPipeFilename, const std::string& botPipeFilename, const GLfloat xDisplacement, const GLfloat ySpace = 0.3);

    /**
     * These 3 function should be called in the order of: create, update, checkCollision. They should be called in the most frequently called event. (Idle or Timer);
     */
    void createPipe();
    void updatePipes();
    bool checkCollision();

    void draw();
};

#endif
