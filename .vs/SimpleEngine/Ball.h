#pragma once
#include <SDL.h>
#include <iostream>
#include <algorithm>
#include <random>
#include <thread>
#include <vector>
#include "Brick.h"

class Ball 
{
public:
	void initialize(int h, int w);
	void setStartingPosition();

	SDL_Rect moveBall();

	const SDL_Rect* getCurrentPosition() const { return &ballRect; }

	void changeHorizontalVelocity() { horizontalVelocity = -horizontalVelocity; }
	void changeVerticalVelocity() { verticalVelocity = -verticalVelocity; }

	bool isOutOfBounds() const { return outOfBounds; }

	int getVerticalSize() const { return vertical + ballScaling; }
	int getHorizontalSize() const { return horizontal + ballScaling; }

private:

	SDL_Rect ballRect;
	int height;
	int width;
	int vertical, horizontal;
	int horizontalVelocity, verticalVelocity;
	const int ballScaling = 13;
	bool outOfBounds = false;
};