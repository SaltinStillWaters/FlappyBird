#ifndef DIMENSION_H
#define DIMENSION_H


class Dimension {
    public:
        float xLeft;
        float xRight;
        float yBot;
        float yTop;

        Dimension(float xLeft, float xRight, float yBot, float yTop);

        bool checkCollision(const Dimension& dimension);
        void updateX(float offset);

    private:
        bool checkXCollision(const Dimension& dimension);
        bool checkYCollision(const Dimension& dimension);
};


#endif //DIMENSION_H