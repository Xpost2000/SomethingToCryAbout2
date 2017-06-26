#pragma once
#include <string>
#include "dllDef.h"
#include <SDL2\SDL.h>
class Window
{
public:
	OATS_LIB_API Window(std::string name, int w, int h);
	OATS_LIB_API Window();
	OATS_LIB_API~Window();
	OATS_LIB_API void CreateWindow();
	OATS_LIB_API void Refresh();
	OATS_LIB_API SDL_Window* returnWindowHandle();
	SDL_Event event;
private:
	int w, h;
	std::string name;
	SDL_Window* window;
	SDL_GLContext ogl;
};

