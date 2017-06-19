#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Game.h"

/*
The New SomethingToCryAbout Engine (not trademarked).

This is a top down shooter game engine. Fairly barebones
but works :) This version is made using OpenGL and not the SDL2 renderer
*/
int main(int argc, char** argv){
	Game game;
	game.InitGame();
	game.RunGame();
	return 0;
}