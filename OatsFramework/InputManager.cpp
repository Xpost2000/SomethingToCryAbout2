#include "InputManager.h"


InputManager::InputManager()
{
}


InputManager::~InputManager()
{
}

bool InputManager::isKeyPressed(int sdlScanCode, std::function<void()> action){
	if (internalKeyState[sdlScanCode]){
		action();
		return true;
	}
	return false;
}

void InputManager::Update(){
	// Update the event queue.
	const Uint8* interalKeyState = SDL_GetKeyboardState(0);
	internalKeyState = const_cast<Uint8*>(interalKeyState);
	SDL_GetMouseState((int*)&coords.x, (int*)&coords.y);
}

void InputManager::PollEvents(std::function<void(SDL_Event*)> func){
	while (SDL_PollEvent(&event)){
		func(&event);
	}
}