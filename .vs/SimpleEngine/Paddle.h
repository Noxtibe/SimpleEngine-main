#pragma once
#include <iostream>
#include <SDL.h>
#include "Actor.h"

class Paddle
{
public:

	//Paddle();
	void setParams(int w) { width = w; };
	SDL_Rect paddleRect() { return { paddleX, paddleY, 80, 20 }; };
	void setPaddlePositions(int w, int h);
	int getPaddleX() { return paddleX; }
	int getPaddleY() { return paddleY; }
	void moveLeft();
	void moveRight();

private:

	int width;
	int paddleX = 0, paddleY = 0;
	int paddleSpeed = 2;
};

