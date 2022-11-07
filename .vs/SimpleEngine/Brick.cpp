#include "Brick.h"

Brick::Brick()
{
	isBrickHit = false;
	currentHealth = 1;
	maxHealth = 1;
}

Brick::Brick(int verticalSpacing, int horizontalSpacing, int life)
{
	currentHealth = life;
	maxHealth = life;
	isBrickHit = false;
	rect = { verticalSpacing, horizontalSpacing, brickWidth, brickHeight };
}

void Brick::hit()
{
	currentHealth--;
	if (currentHealth == 0)
	{
		isBrickHit = true;
	}
}
