#pragma once
#include <Oats\GameStateEnum.h>
#include <Oats\Window.h>
#include <Oats\ResourceManager.h>
#include <Oats\Shader.h>
#include <Oats\VertexBuffer.h>
#include <Oats\VertexArray.h>
#include <Oats\glTexture.h>
#include <Oats\Renderer2D.h>
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

