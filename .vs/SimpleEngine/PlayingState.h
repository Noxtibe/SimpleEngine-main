#pragma once
#include <SDL.h>
#include <memory.h>
#include <thread>
#include <vector>
#include <algorithm>

#include "MainMenuState.h"
#include "GameState.h"
#include "InputManager.h"
#include "Paddle.h"
#include "Renderer.h"
#include "Ball.h"
#include "Bricks.h"
#include "Brick.h"
#include "CollisionManager.h"

class PlayingState : public GameState
{
public:

    PlayingState(std::shared_ptr<Renderer> renderer);
    virtual void update() override;
    virtual void display() override;
    virtual void handleEvent() override;
    virtual std::unique_ptr<GameState> nextState() override;
    virtual bool isActive() override { return active; };

private:

    int lives = 5;
    bool active = true;
    bool exitToMenu = false;
    Status status;
    CollisionManager collisionManager;
    InputManager inputManager;
    std::shared_ptr<Renderer> renderer;
    Bricks bricks = Bricks();
    Paddle paddle = Paddle();
    Ball ball = Ball();
    SDL_Rect paddlePosition;
    SDL_Rect ballPosition;
};

