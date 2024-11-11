#ifndef HITBOX_H
#define HITBOX_H


class Hitbox {
    public:
        float xLeft;
        float xRight;
        float yBot;
        float yTop;

        float pipeWidth = 0.33814;

        Hitbox(float xLeft, float xRight, float yBot, float yTop);

        bool checkCollision(const Hitbox& hitbox);
        void reshape(int width, int height);
        void updateX(float offset);

    private:
        bool checkXCollision(const Hitbox& hitbox);
        bool checkYCollision(const Hitbox& hitbox);
};


#endif //HITBOX_H