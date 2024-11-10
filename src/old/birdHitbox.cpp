#include "birdHitbox.h"
#include "dimension.h"
#include <cmath>
#include <stdexcept>

BirdHitbox::BirdHitbox(const Dimension& dimension, const float grv)
    : dimension(dimension), grv(grv), ySpd(0) {
        if (grv >= 0) {
            throw std::invalid_argument("'grv' must be negative\n");
        }
}

void BirdHitbox::jump(float newYSpd) {
    if (newYSpd <= 0) {
        throw std::invalid_argument("'newYSpd' must be positive\n");
    }
    
    ySpd = newYSpd;
}

void BirdHitbox::update() {
    dimension.yTop += ySpd;
    dimension.yBot += ySpd;
    
    if (std::fabs(ySpd + grv) < std::fabs(MAX_Y_SPD)) {
        ySpd += grv;
    }
}