#ifndef COLLIDE_H
#define COLLIDE_H

#include "dimension.h"
#include <deque>

/**
 * Performs all collision detection.
 * Class must be instantiated only once. (Might be turned into a singleton in the near future.)
 * 
 * ~Flappy Bird Pipe Structure~
 *  _________________________________________________
 *               ______                         ^
 *              |      |                        |
 *              |      |   <-- Top pipe         -- Y_TOP_LIMIT
 *              |      |  
 *              |______|  
 *              
 *              (ySpace)   <-- Opening
 *               ______   
 *     (yLower) |      |  
 *              |      |                        -- Y_BOT_LIMIT
 *              |      |   <-- Bottom pipe      |
 *              |______|                        v
 *  _________________________________________________
 * 
 */

class Collision {
    public:
        /**
         * Deque that keeps track of all the pipe hitboxes.
         */
        std::deque<Dimension*> pipes;

        Collision() = default;
        ~Collision();

        /**
         * Creates 2 'Pipes' of type 'Dimension'.
         * 
         * @param yLower The y-coordinate of the lower pipe's top.
         * @param ySpace Vertical space between top and bottom pipes
         */
        void createPipe(float yLower, float ySpace);

        /**
         * Updates the pipes' x coordinate as well as destroy pipes behind the 'bird' to save resources,
         * since pipes behind the 'bird' cannot trigger collisions.
         * 
         * Must be called at the same rate as the game's fps.
         * 
         * @param bird The bird's hitbox
         * @param offset The displacement at which the x-coordinate of the pipes' will move at each update
         */
        void update(const Dimension& bird, const float offsetof);

        /**
         * Checks if there is a collision between the 'bird' and the nearest pipe
         */
        bool checkCollision(Dimension bird);

    private:
        /**
         * x-coordinate of the left side of pipes at point of creation.
         */
        const float X_START_LEFT = 1.0f;

        /**
         * Width of a pipe.
         */
        const float PIPE_WIDTH = 0.2f;

        /**
         * y limit of bottom pipe. See figure above for more details.
         */
        const float Y_BOT_LIMIT = -1.0f;

        /**
         * Same with Y_BOT_LIMIT but for the upper pipe. See figure above for more details
         */
        const float Y_TOP_LIMIT = 1.0f;
};

#endif // COLLIDE_H