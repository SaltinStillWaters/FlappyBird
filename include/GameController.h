#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include <iostream>
#include <mutex>


class GameController {
public:
    static GameController* getInstance();

    bool getHasCollided() const;
    void setHasCollided();
    void addScore();

    GameController(const GameController& obj) = delete;

private:
    bool hasCollided;
    unsigned int score;

    //Singleton
    static GameController* instance;
    static std::mutex mtx;
    GameController();
};

#endif //GAME_CONTROLLER_H