#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <memory>
#include "InputManager.h"
#include "GameState.h"
#include "PlayingState.h"

class MainMenuState : public GameState {
public:
    MainMenuState(std::shared_ptr<Renderer> r);
    virtual void update() override;
    virtual void display() override;
    virtual void handleEvent() override;
    virtual std::unique_ptr<GameState> nextState() override;
    virtual bool isActive() override { return active; };
private:
    InputManager inputManager;
    int selectedItem = -1;
    int highlightedPosition = 0;
    bool active = true;
    std::shared_ptr<Renderer> renderer = nullptr;
};

