#pragma once
#include <Oats\GameStateEnum.h>
#include <Oats\Window.h>
#include <Oats\ResourceManager.h>
#include <Oats\Shader.h>
#include <Oats\ClockTimer.h>
#include <Oats\VertexBuffer.h>
#include <Oats\VertexArray.h>
#include <Oats\glTexture.h>
#include <Oats\Renderer2D.h>
#include <Oats\Camera2D.h>
#include "DemoBall.h"
class Game
{
public:
	Game();
	~Game();
	void InitGame();
	void RunGame();
private:
	// Objects for Game
	std::vector<DemoBall> balls;
	//Math Stuff
	glm::mat4 view = glm::mat4();
	glm::mat4 projection = glm::mat4();
	glm::mat4 model = glm::mat4();
	//
	Window *window = nullptr;
	Shader* fragment = nullptr;
	Shader* vertex = nullptr;
	Camera2D* camera = nullptr;
	ShaderProgram* program = nullptr;
	glTexture* tex = nullptr;
	glTexture* bkgrnd = nullptr;
	Renderer2D* renderer = nullptr;
	GameState inState;
	
	int width = 1024, height = 768;
	
	// Functions
	void HandleInput();
	void DrawGame();
	void UpdateGame();
};

