#ifndef SCOREDISPLAY_H
#define SCOREDISPLAY_H

#include "DrawableObj.h"
#include <deque>
#include <string>

class ScoreDisplay {
public:
    ScoreDisplay();

    void display();
    void draw();

private:
    int score = 1235;
    std::deque<DrawableObj*> drawableDigits;
};

#endif // SCOREDISPLAY_H