#pragma once
#include <SDL_rect.h>
#include <thread>
#include <vector>
#include <algorithm>

#include "Brick.h"
#include "Ball.h"

class CollisionManager
{
public:

	void collision(Ball* ball, SDL_Rect paddleRect, std::vector<Brick>* bricks);
	int brickCollisions() { return brickCollisionCounter; };

private:

	SDL_Rect interSectRect = { 0,0,0,0 };
	int brickCollisionCounter = 0;
	static bool paddleCollision(int horizontal, int vertical, SDL_Rect paddleRect);
	static bool paddleCollisionAtEnd(int horizontal, int x, int w);
	bool ballBrickCollision(const SDL_Rect* ballRect, std::vector<Brick>* bricks);
};
