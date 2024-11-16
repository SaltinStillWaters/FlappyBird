#include "GameController.h"

#include "Bird.h"

#include <iostream>
#include <Windows.h>
#include <mmsystem.h>

//no need for destructor. All * members exist outside the class and destroyed in main.cpp
//resettables are deleted by their respective implementing classes
GameController* GameController::instance = nullptr;

GameController::GameController() : hasCollided(false) {}

GameController* GameController::getInstance() {
    if (instance == nullptr) {
        instance = new GameController();
    }
    return instance;
}

bool GameController::getHasCollided() const { return hasCollided; }

bool GameController::getHasStarted() const { return hasStarted; }

void GameController::setHasCollided() { 
    hasCollided = true; 
    PlaySoundW(collideSound, 0, SND_FILENAME | SND_ASYNC);
}

void GameController::setHasStarted() { hasStarted = true; }

void GameController::addScore() { 
    scoreDisplay->setScore();
    PlaySoundW(addScoreSound, 0, SND_FILENAME | SND_ASYNC);
}

void GameController::addResettable(Resettable* r) {
    resettables.push_back(r);
}

void GameController::setScoreDisplay(ScoreDisplay* scoreDisplay) {
    this->scoreDisplay = scoreDisplay;
    addResettable(scoreDisplay);
}

void GameController::reset() {
    hasStarted = false;
    hasCollided = false;

    for (Resettable* r : resettables) {
        r->reset();
    }
}

void GameController::clickHandler() {
    if      (!hasStarted) { hasStarted = true; }
    else if (hasCollided) { reset(); }
}