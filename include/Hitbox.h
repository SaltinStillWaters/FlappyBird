#ifndef HITBOX_H
#define HITBOX_H


class Hitbox {
    public:
        float xLeft;
        float xRight;
        float yBot;
        float yTop;

        Hitbox(float xLeft, float xRight, float yBot, float yTop);

        bool checkCollision(const Hitbox& hitbox) const;
        void updateX(float offset);
        void updateY(float offset);
        void printCoords();
    private:
        bool checkXCollision(const Hitbox& hitbox) const;
        bool checkYCollision(const Hitbox& hitbox) const;
};


#endif //HITBOX_H