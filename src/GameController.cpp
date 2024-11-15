#include "GameController.h"

#include "Bird.h"

#include <iostream>
#include <mutex>


GameController* GameController::instance = nullptr;
std::mutex GameController::mtx;

GameController::GameController() : hasCollided(false), score(0) {}

GameController* GameController::getInstance() {
    if (instance == nullptr) {
        std::lock_guard<std::mutex> lock(mtx);
        if (instance == nullptr) {
            instance = new GameController();
        }
    }

    return instance;
}

bool GameController::getHasCollided() const { return hasCollided; }

bool GameController::getHasStarted() const { return hasStarted; }

void GameController::setHasCollided() { hasCollided = true; }

void GameController::setHasStarted() { hasStarted = true; }

void GameController::addScore() { ++score; }

void GameController::addResettable(Resettable* r) {
    resettables.push_back(r);
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