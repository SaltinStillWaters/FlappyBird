#ifndef PIPES_H
#define PIPES_H

#include "DrawableObj.h"
#include "Hitbox.h"
#include "GameController.h"

#include <string>
#include <deque>
#include <random>
#include <limits>
#include <mutex>

class Pipes {
public:
    //change to higher value if needed
    static float constexpr Y_MIN = std::numeric_limits<float>::min();
    
    //change to lower value if needed
    static float constexpr Y_MAX = std::numeric_limits<float>::max();
    
    ~Pipes();
    Pipes() = delete;
    Pipes(const Pipes& obj) = delete;

    static Pipes* getInstance(GameController* controller, const Hitbox* birdHitbox,
                              const std::string& topPipeFilename, const std::string& botPipeFilename,
                              const GLfloat xDisplacement, const GLfloat ySpace = 0.5);

    void update();
    void draw();

private:
    std::deque<DrawableObj*> pipes;
    std::deque<Hitbox*> hitboxes;

    const Hitbox* birdHitbox;
    GameController* controller;

    const GLfloat xDisplacement;
    const GLfloat ySpace;
    static float constexpr pipeWidth = .33814f * 9.f / 16.f; //temp (important)

    static unsigned int constexpr updatesNeeded = 90; //change this as needed
    static unsigned int updateCount;
    
    //Random
    std::mt19937* randMt;
    std::uniform_int_distribution<int>* distrib;

    /**
     * These 3 function should be called in the order of: create, update, checkCollision.
     */
    void createPipe();
    void updatePipes();
    void checkCollision();

    //Singleton
    static Pipes* instance;
    static std::mutex mtx;
    Pipes(GameController* controller, const Hitbox* birdHitbox, const std::string& topPipeFilename, const std::string& botPipeFilename, 
          const GLfloat xDisplacement, const GLfloat ySpace = 0.5);
};

#endif
