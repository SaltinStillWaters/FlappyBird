#ifndef BIRD_H
#define BIRD_H

#include "dimension.h"

/**
 * Represents the bird's hitbox.
 * 
 * Only 1 instance of this class must be present, 
 * therefore it is possible that it may be turned into a singleton in the future.
 */
class BirdHitbox {
    public:
        /**
         * Real-time coordinates of the bird
         */
        Dimension dimension;
    
    private:
        /**
         * It's vertical displacement per unit of game time.
         * (Literally the y-speed)
         * Though, it's called speed, it is actually a vector. (Might be renamed to yVelocity in the future)
         */
        float ySpd;

        /**
         * Gravity.
         * The rate at which ySpd is decreased per unit of game time.
         */
        const float grv;

        /**
         * The max y-speed it can reach.
         * It is a scalar, so no need to specify direction (sign).
         */
        const float MAX_Y_SPD = 0.1;

    public:
        /**
         * Throws invalid_argument exception when grv is non-negative.
         * 
         * @param dimension dimensions of bird.
         * @param grv gravity. Must be negative.
         */
        BirdHitbox(const Dimension& dimension, float grv);

        /**
         * Updates the bird's ySpd, which signifies a jump.
         * Throws invalid_argument exception when newSpd is non-positive
         * 
         * @param newYSpd The new value of ySpd. Must be positive
         */
        void jump(float newYSpd);

        /**
         * Updates the nessecary object members needed for collision checking and movement.
         * Must be called once per unit of game time.
         */
        void update();
};

#endif //BIRD_H