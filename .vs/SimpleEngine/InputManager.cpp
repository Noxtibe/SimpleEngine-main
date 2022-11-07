#include "InputManager.h"
#include <SDL_scancode.h>

void InputManager::readEvent()
{
	if (event.type == SDL_KEYDOWN)
	{
		if (KeyStillDown())
			return;

		keymap[event.key.keysym.sym] = true;
	}

	if (event.type == SDL_KEYUP)
		keymap[event.key.keysym.sym] = false;
}

InputAction InputManager::handle()
{
	SDL_PollEvent(&event);
	readEvent();

	if (event.type == SDL_QUIT || isKeyPressed(SDLK_ESCAPE) || isKeyPressed(SDL_QUIT))
		return QUIT_GAME;

	else if ((isKeyPressed(SDLK_LEFT) || isKeyPressed(SDLK_q)))
		return MOVE_LEFT;

	else if (isKeyPressed(SDLK_RIGHT) || isKeyPressed(SDLK_d))
		return MOVE_RIGHT;

	else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE)
		return TOGGLE_PAUSE;

	else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_DOWN)
		return MOVE_DOWN;

	else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_s)
		return MOVE_DOWN;

	else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_UP)
		return MOVE_UP;

	else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_w)
		return MOVE_UP;

	else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN)
		return ENTER;

	else
		return NOTHING;
}