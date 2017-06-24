#pragma once
#include "dllDef.h"
#include <functional>
#include <SDL2/SDL.h>
/*
TODO: Fix typo
*/
struct MouseCoords{
	int x, y;
};

class InputManager
{
public:
	OATS_LIB_API InputManager();
	OATS_LIB_API ~InputManager();
	OATS_LIB_API void Update();
	// Callback should be a case handler.
	OATS_LIB_API void PollEvents(std::function<void(SDL_Event*)> callBack);
	OATS_LIB_API bool isKeyPressed(int sdlScanCode, std::function<void()> action);
private:
	SDL_Event event;
	Uint8 *internalKeyState;
	MouseCoords coords;
};

