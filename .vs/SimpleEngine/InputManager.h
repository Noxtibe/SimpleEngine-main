#pragma once
#include <map>
#include <SDL.h>
#include "InputAction.h"

class InputManager 
{
public:

	InputAction handle();


private:

	std::map<int, bool> keymap;
	SDL_Event event;
	void readEvent();
	bool isKeyPressed(SDL_Keycode key) { return keymap[key]; }
	bool KeyStillDown() { return event.key.repeat != 0; }
};
