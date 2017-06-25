#pragma once
#include "dllDef.h"
#include <functional>
#include <SDL2/SDL.h>
/*
 Mouse Coordinates Structure.
 Essentially vec2 glorified into a struct.
*/
struct MouseCoords{
	int x, y; // Coordinate holders
};

/*
	|InputManager Class|
	====================
	Neatly wraps and manages Library / API specific 
	input handling. Easy understandable wrapper for all types of people.

	-- Functions
	Update() // Update the mouse coordinates and current keyboard state.
	PollEvents() // Use a event polling system
	isKeyPressed() // Use a scancode based system
	isKeyReleased() // Check if key is not pressed.
*/
class InputManager
{
public:
	// Constructor not needed
	int GetMouseX() { return coords.x; };
	int GetMouseY() { return coords.y; };
	OATS_LIB_API InputManager();
	OATS_LIB_API ~InputManager();
	//Update the mouse coordinates and update Keyboard state
	OATS_LIB_API void Update();
	// Callback should be a case handler.
	OATS_LIB_API void PollEvents(std::function<void(SDL_Event*)> callBack);
	// Check if key is pressed ( boolean value )
	OATS_LIB_API bool isKeyPressed(int sdlScanCode, std::function<void()> action);
	// Check if key is released ( boolean value )
	OATS_LIB_API bool isKeyReleased(int sdlScanCode, std::function<void()> action);
private:
	// Event struct for PollEvents style input
	SDL_Event event;
	// Holds current keyboardState
	Uint8 *internalKeyState;
	MouseCoords coords;
};

