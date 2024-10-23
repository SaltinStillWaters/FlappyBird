#ifndef COLLIDE_H
#define COLLIDE_H

#include "dimension.h"
#include <deque>

// Collision Class Declaration
class Collision {
    public:
        std::deque<Dimension*> pipes;

        Collision() = default;
        ~Collision();

        void createPipe(float yLower, float ySpace);
        void update(const Dimension& bird);
        bool checkCollision(Dimension bird);

    private:
        // Configuration Constants
        const float X_START_LEFT = 1.0f;
        const float PIPE_WIDTH = 0.2f;
        const float Y_BOT_LIMIT = -1.0f;
        const float Y_TOP_LIMIT = 1.0f;
};

#endif // COLLIDE_H