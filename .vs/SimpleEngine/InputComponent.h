#pragma once
#include <SDL_stdinc.h>
#include "Actor.h"

class InputComponent
{
public:

	InputComponent(Actor* ownerP);
	InputComponent() = delete;
	InputComponent(const InputComponent&) = delete;
	InputComponent& operator=(const InputComponent&) = delete;

	void processInput(const Uint8* keyState);

	void setMaxForwardSpeed(float maxForwardSpeedP);
	void setMaxAngularSpeed(float maxAngularSpeedP);
	void setForwardKey(int key);
	void setBackKey(int key);
	void setClockwiseKey(int key);
	void setCounterClockwiseKey(int key);

private:

	float maxForwardSpeed;
	float maxAngularSpeed;

	int forwardKey;
	int backKey;
	int clockwiseKey;
	int counterClockwiseKey;
};

