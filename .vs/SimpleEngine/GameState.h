#pragma once
#include <SDL.h>
#include <memory>
#include "Renderer.h"

class GameState {
public:
    virtual void update() = 0;
    virtual void display() = 0;
    virtual void handleEvent() = 0;
    virtual std::unique_ptr<GameState> nextState() = 0;
    virtual bool isActive() = 0; // temp
};

