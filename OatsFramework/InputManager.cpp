#include "InputManager.h"

/*
	As of right now the whole class is a basic wrapper around API specific things
	:D
*/


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
	SDL_GetRelativeMouseState((int*)&relative_coords.x, (int*)&relative_coords.y);
}

void InputManager::PollEvents(std::function<void(SDL_Event*)> func){
	while (SDL_PollEvent(&event)){
		func(&event);
	}
}

bool InputManager::isKeyReleased(int sdlScanCode, std::function<void()> action){
	if (!internalKeyState[sdlScanCode]){
		action;
		return true;
	}
	return false;
}

bool InputManager::isMouseButtonPressed(MouseButton type){
	if (type == MouseButton::LEFT_CLICK){
		if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
		return true;
	}
	if (type == MouseButton::RIGHT_CLICK){
		if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT))
		return true;
	}
	return false;
}