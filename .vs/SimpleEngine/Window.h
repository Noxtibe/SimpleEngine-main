#pragma once
#include<SDL.h>

constexpr int WINDOW_WIDTH = 1024; // constexpr varaible qui existe au moment de la compilation
constexpr int WINDOW_HEIGHT = 768;

class Window
{
public :

	Window() = default;  // Variable déjà initialisé par défaut
	Window(const Window&) = delete;
	Window& operator =(const Window&) = delete;

	bool initialize();
	void close();

	// {} Beaucoup plus opti pour le compilateur
	SDL_Window* getSDLWindow() const{ return SDLWindow; }
	int getWidth() const { return width; }
	int getHeight() const { return height; }

private :

	SDL_Window* SDLWindow {nullptr}; // Toujours initialisé le pointeur par nullptr pour que le compilateur ne lise rien
	int width {WINDOW_WIDTH};
	int height {WINDOW_HEIGHT};
};

