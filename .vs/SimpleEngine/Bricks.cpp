#include "Bricks.h"

void Bricks::InitializeBricks(int topSpacing)
{
	brickVector.clear();

	int horizontalSpacing = topSpacing;

	for (int i = 0; i < brickRows; i++)
	{
		int verticalSpacing = 10;
		for (int j = 0; j < brickColumns; j++)
		{
			brickVector.emplace_back(verticalSpacing, horizontalSpacing, brickRows - i);
			verticalSpacing += 88;
		}
		horizontalSpacing += 40;
	}
}
