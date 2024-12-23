#ifndef PIPES_H
#define PIPES_H

#include "DrawableObj.h"
#include "Hitbox.h"
#include "GameController.h"

#include <string>
#include <deque>
#include <random>
#include <limits>

class Pipes : public Resettable {
public:
    //change to higher value if needed
    static float constexpr Y_MIN = std::numeric_limits<float>::lowest();
    
    //change to lower value if needed
    static float constexpr Y_MAX = std::numeric_limits<float>::max();
    
    void update();
    void draw();
    
    void reset() override;

    //Singleton
    ~Pipes();
    Pipes() = delete;
    Pipes(const Pipes& obj) = delete;

    static Pipes* getInstance(GameController* controller, const Hitbox* birdHitbox,
                              const std::string& topPipeFilename, const std::string& botPipeFilename,
                              const GLfloat xDisplacement, const GLfloat ySpace = 0.5);

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

    Pipes(GameController* controller, const Hitbox* birdHitbox, const std::string& topPipeFilename,
          const std::string& botPipeFilename, const GLfloat xDisplacement, const GLfloat ySpace = 0.5);
};

#endif
