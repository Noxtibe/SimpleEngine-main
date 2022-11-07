#include "Log.h"
#include <SDL_log.h>
#include <SDL_error.h>

void Log::info(const string& message) // passer l'objet en const reference pour un objet complexe et évité des copies dans la mémoire
{
	SDL_Log(message.c_str());
}

void Log::error(LogCategory category, const string& message)
{
	SDL_LogError(static_cast<int>(category), "%s | SDL: %s", message.c_str(), SDL_GetError());
}
