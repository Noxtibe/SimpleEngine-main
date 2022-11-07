#pragma once
#include <iostream>
#include <SDL.h>
#include <memory>
#include <thread>

#include "InputManager.h"
#include "Ball.h"
#include "Bricks.h"
#include "Paddle.h"
#include "Renderer.h"
#include "GameState.h"
#include "PlayingState.h"
#include "MainMenuState.h"

#include "Actor.h"

class GameManager 
{
public :

	static GameManager& instance()
	{
		static GameManager inst;
		return inst;
	}

public:

	void init();
	void play();
	void quit();
	bool gameEnded = false;

	void addActor(Actor* actor);
	void removeActor(Actor* actor);
	

private:

	std::shared_ptr<Renderer> renderer = std::make_shared<Renderer>(Renderer());
	void processInput();
	void update(float dt);
	bool isUpdatingActors;
	vector<Actor*> actors;
	vector<Actor*> pendingActors;
};



/*public:

	void init();
	void play();
	void quit();
	bool gameEnded = false;



private:

	std::shared_ptr<Renderer> renderer = std::make_shared<Renderer>(Renderer());*/
