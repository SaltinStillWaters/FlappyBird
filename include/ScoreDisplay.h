#ifndef SCOREDISPLAY_H
#define SCOREDISPLAY_H

#include "DrawableObj.h"
#include "Resettable.h"

#include <deque>
#include <string>

class ScoreDisplay : public Resettable {
public:
    void draw() const;
    void setScore();

    void reset() override;

    //Singleton
    static ScoreDisplay* getInstance();
    ScoreDisplay(const ScoreDisplay& obj) = delete;
private:
    int score = 0;
    GLfloat const spacing = .15f;
    std::deque<DrawableObj*> drawableDigits;
    
    GLfloat const scale = 0.1f;
    GLfloat const yOffset = .75f; 

    void clearDeque();
    void updateScore();

    //Singleton
    static ScoreDisplay* instance;
    
    ScoreDisplay();
};

#endif // SCOREDISPLAY_H