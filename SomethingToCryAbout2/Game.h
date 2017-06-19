#pragma once
#include "GameStateEnum.h"
#include "Window.h"
#include "Shader.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "ShaderProgram.h"
#include "glTexture.h"
#include "Renderer2D.h"
class Game
{
public:
	Game();
	~Game();
	void InitGame();
	void RunGame();
private:
	//Math Stuff
	glm::mat4 view = glm::mat4();
	glm::mat4 projection = glm::mat4();
	glm::mat4 model = glm::mat4();
	//
	Window *window = nullptr;
	Shader* fragment = nullptr;
	Shader* vertex = nullptr;
	ShaderProgram* program = nullptr;
	glTexture* tex = nullptr;
	Renderer2D* renderer = nullptr;
	GameState inState;
	// Functions
	void HandleInput();
	void DrawGame();
	void UpdateGame();
};

