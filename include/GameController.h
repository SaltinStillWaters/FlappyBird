#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "Resettable.h"

#include <vector>
#include <mutex>


class GameController {
public:
    bool getHasCollided() const;
    bool getHasStarted() const;
    void setHasCollided();
    void setHasStarted();

    void addScore();

    void addResettable(Resettable* r);

    void clickHandler();

    //Singleton
    GameController(const GameController& obj) = delete;

    static GameController* getInstance();
private:
    std::vector<Resettable*> resettables;
    bool hasCollided;
    unsigned int score;
    bool hasStarted;

    void reset();

    //Singleton
    static GameController* instance;
    static std::mutex mtx;

    GameController();
};

#endif //GAME_CONTROLLER_H