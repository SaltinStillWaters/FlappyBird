#include "DrawableObj.h"

#include <deque>
#include <string>


class ScoreDisplay {
    int score = 5;
    int digits = 1;
    std::deque<DrawableObj*> drawableDigits;

    ScoreDisplay() {
        for (int x = 0; x < 10; ++x) {
            std::string str = std::to_string(x);
            DrawableObj::type(str, GL_QUADS, "numbers/" + str + ".data", &DrawableObj::formatVertexColor);
        }
    }

    void display() {
        const float numWidth = 0.1f;
        const std::string str = std::to_string(score);

        if (digits % 2) {
            int mid = digits/2;

            drawableDigits.push_back(DrawableObj::create(std::to_string(str[mid])));

            for (int x = 0; x < digits/2; ++x) {
                drawableDigits.push_back(DrawableObj::create(std::to_string(str[mid + x + 1])));
                drawableDigits.back()->setOffset(numWidth/2 + x * numWidth, 0);
                
                drawableDigits.push_front(DrawableObj::create(std::to_string(str[mid - (x + 1)])));
                drawableDigits.front()->setOffset(numWidth/2 - x * numWidth, 0);
            }
        }
    }

    void draw() {
        for (DrawableObj* drawable : drawableDigits) {
            drawable->draw();
        }
    }
};