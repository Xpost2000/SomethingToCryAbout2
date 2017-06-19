#pragma once
#include <string>
#include <SDL2\SDL.h>
class Window
{
public:
	Window(std::string name, int w, int h);
	Window();
	~Window();
	void CreateWindow();
	void Refresh();
	SDL_Event event;
private:
	int w, h;
	std::string name;
	SDL_Window* window;
	SDL_GLContext ogl;
};

