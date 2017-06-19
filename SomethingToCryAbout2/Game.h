#pragma once
#include "GameStateEnum.h"
#include "Window.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "glTexture.h"
class Game
{
public:
	Game();
	~Game();
	void InitGame();
	void RunGame();
private:
	Window *window = nullptr;
	Shader* fragment = nullptr;
	Shader* vertex = nullptr;
	ShaderProgram* program = nullptr;
	glTexture* tex = nullptr;
	GameState inState;
	// Functions
	void HandleInput();
	void DrawGame();
	void UpdateGame();
	// Temporary OGL stuff
	GLuint vbo, vao;
};

