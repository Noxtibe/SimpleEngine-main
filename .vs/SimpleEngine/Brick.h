#pragma once
#include <iostream>
#include <SDL.h>

class Brick 
{
public:

	Brick();
	Brick(int verticalSpacing, int horizontalSpacing, int life);

	SDL_Rect rect{};
	void hit();
	bool isHit() { return isBrickHit; };
	int getHealth() { return currentHealth; };

private:

	bool isBrickHit = false;
	int brickWidth = 80;
	int brickHeight = 34;
	int currentHealth;
	int maxHealth;
};