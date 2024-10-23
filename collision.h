#ifndef COLLIDE_H
#define COLLIDE_H

#include <deque>

// Dimension Class Declaration
class Dimension {
    public:
        float xLeft;
        float xRight;
        float yBot;
        float yTop;

        // Constructor
        Dimension(float xLeft, float xRight, float yBot, float yTop);

        // Public Methods
        bool checkCollision(const Dimension& dimension);
        void updateX(float offset);

    private:
        // Private Methods for X and Y Collision Detection
        bool checkXCollision(const Dimension& dimension);
        bool checkYCollision(const Dimension& dimension);
};

// Collide Class Declaration
class Collide {
    public:
        std::deque<Dimension*> pipes;

        // Constructor
        Collide() = default;
        ~Collide();

        // Public Methods
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