#ifndef PIPES_H
#define PIPES_H

#include "DrawableObj.h"
#include "Hitbox.h"
#include "ArrayBuffer.h"
#include <deque>
#include <string>
#include <random>
#include <mutex>

/*
To Do
add birdHitbox to constructor
*/
class Pipes {
public:
    Pipes() = delete;
    Pipes(const Pipes& obj) = delete;

    static Pipes* getInstance(const std::string& topPipeFilename, const std::string& botPipeFilename,
                              const GLfloat xDisplacement, const GLfloat ySpace = 0.5);

    /**
     * These 3 function should be called in the order of: create, update, checkCollision. 
     * They should be called in the most frequently called event. (Idle or Timer);
     */
    void createPipe();
    void updatePipes();
    bool checkCollision();

    void draw();

private:
    std::deque<DrawableObj*> pipes;
    std::deque<Hitbox*> hitboxes;

    const Hitbox* birdHitbox = new Hitbox(-0.5, 0, -0.5, 0.5);

    ArrayBuffer* topPipeVBO;
    ArrayBuffer* botPipeVBO;
    const GLfloat xDisplacement;
    const GLfloat ySpace;
    static float constexpr pipeWidth = .33814; //temp

    static unsigned int constexpr updatesNeeded = 120; //change this as needed
    static unsigned int updateCount;
    
    //Random
    std::mt19937* randMt;
    std::uniform_int_distribution<int>* distrib;

    //Singleton
    static Pipes* instance;
    static std::mutex mtx;
    Pipes(const std::string& topPipeFilename, const std::string& botPipeFilename, 
          const GLfloat xDisplacement, const GLfloat ySpace = 0.5);

};

#endif