#include "ScoreDisplay.h"
#include <iostream>
#include <mutex>


//static members
ScoreDisplay* ScoreDisplay::instance = nullptr;
std::mutex ScoreDisplay::mtx;

ScoreDisplay *ScoreDisplay::getInstance() {
    if (instance == nullptr) {
        std::lock_guard<std::mutex> lock(mtx);
        if (instance == nullptr) {
            instance = new ScoreDisplay();
        }
    }

    return instance;
}

ScoreDisplay::ScoreDisplay() {
    for (int x = 0; x < 10; ++x) {
        std::string str = std::to_string(x);
        std::string filename = "numbers/" + str + ".data";

        DrawableObj::type(str, GL_QUADS, filename,
                          &DrawableObj::formatVertexColor);
    }
}

void ScoreDisplay::updateScore() {
    const std::string str = std::to_string(score);
    const int digits = str.size();

    int mid = digits / 2;

    if (digits % 2) {
        /*
          Cannot convert from char to std::string lmao.
          Since char is of integral type, there are some funny that will happen
          if we use it instead of std::string
        */
        std::string midStr = { str[mid] };
        drawableDigits.push_back(DrawableObj::create(midStr));
        drawableDigits.back()->setScale(0.1);
  
        for (int x = 0; x < digits / 2; ++x) {
            std::string rightStr = { str[mid + x + 1] };
            drawableDigits.push_back(DrawableObj::create(rightStr));
            drawableDigits.back()->setOffset(spacing + x * spacing, 0);
            drawableDigits.back()->setScale(0.1);

            std::string leftStr = { str[mid - (x + 1)] };
            drawableDigits.push_front(DrawableObj::create(leftStr));
            drawableDigits.front()->setOffset(-(spacing + x * spacing), 0);
            drawableDigits.front()->setScale(0.1);
        }
    } else {
        for (int x = 0; x < digits / 2; ++x) {
            std::string rightStr = { str[mid + x] };
            drawableDigits.push_back(DrawableObj::create(rightStr));
            drawableDigits.back()->setOffset(spacing/2 + x * spacing, 0);
            drawableDigits.back()->setScale(0.1);

            std::string leftStr = { str[mid - (x + 1)] };
            drawableDigits.push_front(DrawableObj::create(leftStr));
            drawableDigits.front()->setOffset(-(spacing/2 + x * spacing), 0);
            drawableDigits.front()->setScale(0.1);
        }
    }
}

void ScoreDisplay::clearDeque() {
    for (DrawableObj* drawable : drawableDigits) {
        delete drawable;
    }

    drawableDigits.clear();
}

void ScoreDisplay::draw() const {
    for (DrawableObj* drawable : drawableDigits) {
        drawable->draw();
    }
}

void ScoreDisplay::setScore(int score) {
    this->score = score;

    clearDeque();
    updateScore();
}