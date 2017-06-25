#pragma once
/*
	Primitive GameState enumeration.
	Carries the bare minimum prefered states
*/
enum class GameState{
	GAME_RUNNING,
	GAME_QUIT,
	GAME_PAUSE,
	GAME_MENU,
	GAME_LOSE,
	GAME_FINISH
};