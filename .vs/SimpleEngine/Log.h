#pragma once
#include <string>
#include <SDL_log.h>

using std::string;

// WRAPPER 
enum class LogCategory
{
	Application = SDL_LOG_CATEGORY_APPLICATION,
	Assert = SDL_LOG_CATEGORY_ASSERT,
	Audio = SDL_LOG_CATEGORY_AUDIO,
	Error = SDL_LOG_CATEGORY_ERROR,
	Input = SDL_LOG_CATEGORY_INPUT,
	Render = SDL_LOG_CATEGORY_RENDER,
	System = SDL_LOG_CATEGORY_SYSTEM,
	Test = SDL_LOG_CATEGORY_TEST,
	Video = SDL_LOG_CATEGORY_VIDEO
};

class Log
{
public :

	Log() = delete;  // Pour empêcher d'instancier
	Log(const Log&) = delete; // No instantiate
	Log& operator=(const Log&) = delete; // Supprime l'opérateur =

	static void info(const string& message);
	static void error(LogCategory category, const string& message);
};

