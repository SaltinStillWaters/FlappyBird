#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "Resettable.h"
#include "ScoreDisplay.h"
#include <vector>


class GameController {
public:
    bool getHasCollided() const;
    bool getHasStarted() const;
    void setHasCollided();
    void setHasStarted();

    void addScore();

    void addResettable(Resettable* r);
    void setScoreDisplay(ScoreDisplay*);

    void clickHandler();

    //Singleton
    GameController(const GameController& obj) = delete;

    static GameController* getInstance();
private:
    std::vector<Resettable*> resettables;
    ScoreDisplay* scoreDisplay;
    bool hasCollided;
    bool hasStarted;
    
    void reset();

    //Singleton
    static GameController* instance;

    GameController();
};

#endif //GAME_CONTROLLER_H