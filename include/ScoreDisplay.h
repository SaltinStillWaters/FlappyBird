#ifndef SCOREDISPLAY_H
#define SCOREDISPLAY_H

#include "DrawableObj.h"
#include <deque>
#include <string>
#include <mutex>

class ScoreDisplay {
public:
    void draw() const;
    void setScore(int score);

    //Singleton
    static ScoreDisplay* getInstance();
    ScoreDisplay(const ScoreDisplay& obj) = delete;
private:
    int score = 0;
    GLfloat const spacing = .15f;
    std::deque<DrawableObj*> drawableDigits;
    
    void clearDeque();
    void updateScore();

    //Singleton
    static ScoreDisplay* instance;
    static std::mutex mtx;
    
    ScoreDisplay();
};

#endif // SCOREDISPLAY_H