#ifndef CLOUD_H
#define CLOUD_H

#include "Resettable.h"
#include "DrawableObj.h"

#include <string>
#include <deque>
#include <random>
#include <limits>

class Cloud : public Resettable {
public:
    //change to higher value if needed
    static float constexpr Y_MIN = std::numeric_limits<float>::lowest();
    
    //change to lower value if needed
    static float constexpr Y_MAX = std::numeric_limits<float>::max();
    
    void update();
    void draw();
    
    void reset() override;

    //Singleton
    ~Cloud();
    Cloud() = delete;
    Cloud(const Cloud& obj) = delete;

    static Cloud* getInstance(const std::string& cloudFilename,
                              const GLfloat xDisplacement, 
                              const GLfloat ySpace = 0.5);

private:
    std::deque<DrawableObj*> clouds;

    const GLfloat xDisplacement;
    const GLfloat ySpace;
    static float constexpr cloudWidth = .33814f * 9.f / 16.f; //temp (important)

    static unsigned int constexpr updatesNeeded = 90; //change this as needed
    static unsigned int updateCount;
    
    //Random
    std::mt19937* randMt;
    std::uniform_int_distribution<int>* distrib;

    /**
     * These 2 function should be called in the order of: create, update.
     */
    void createCloud();
    void updateCloud();

    //Singleton
    static Cloud* instance;

    Cloud(const std::string& cloudFilename,
          const GLfloat xDisplacement,
          const GLfloat ySpace = 0.5);
};

#endif