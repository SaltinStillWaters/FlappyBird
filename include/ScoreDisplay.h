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
    ~ScoreDisplay();
    static ScoreDisplay* getInstance();
    ScoreDisplay(const ScoreDisplay& obj) = delete;
private:
    int score = 0;
    GLfloat const spacing = .11f;
    std::deque<DrawableObj*> drawableDigits;
    
    GLfloat const scale = 0.15f;
    GLfloat const yOffset = .8f; 

    void clearDeque();
    void updateScore();

    //Singleton
    static ScoreDisplay* instance;
    
    ScoreDisplay();
};

#endif // SCOREDISPLAY_H