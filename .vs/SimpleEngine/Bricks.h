#pragma once
#include <SDL.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include "Brick.h"

class Bricks 
{
public:

	void InitializeBricks(int topSpacing);
	std::vector<Brick>* getBricks() { return &brickVector; };
	static const int brickRows = 5;
	static const int brickColumns = 9;

private:

	std::vector<Brick> brickVector;
};