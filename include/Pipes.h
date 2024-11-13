#ifndef PIPES_H
#define PIPES_H

#include "DrawableObj.h"
#include "Hitbox.h"
#include "ArrayBuffer.h"
#include "GameController.h"
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
    ~Pipes();
    Pipes() = delete;
    Pipes(const Pipes& obj) = delete;

    static Pipes* getInstance(GameController* controller, const std::string& topPipeFilename, const std::string& botPipeFilename,
                              const GLfloat xDisplacement, const GLfloat ySpace = 0.5);

    /**
     * These 3 function should be called in the order of: create, update, checkCollision. 
     * They should be called in the most frequently called event. (Idle or Timer);
     */
    void createPipe();
    void updatePipes();
    void checkCollision();

    void draw();

private:
    std::deque<DrawableObj*> pipes;
    std::deque<Hitbox*> hitboxes;

    const Hitbox* birdHitbox = new Hitbox(-0.01, 0.01, -5, -5.5);
    GameController* controller;

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
    Pipes(GameController* controller, const std::string& topPipeFilename, const std::string& botPipeFilename, 
          const GLfloat xDisplacement, const GLfloat ySpace = 0.5);
public:
    
};

#endif
