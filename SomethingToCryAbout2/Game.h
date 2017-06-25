#pragma once
#include <Oats\GameStateEnum.h>
#include <Oats\Window.h>
#include <Oats\InputManager.h>
#include <Oats\ResourceManager.h>
#include <Oats\Shader.h>
#include <Oats\ClockTimer.h>
#include <Oats\VertexBuffer.h>
#include <Oats\VertexArray.h>
#include <Oats\glTexture.h>
#include <Oats\Renderer2D.h>
#include <Oats\Camera2D.h>
#include <Oats\Framebuffer.h>
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

	Shader* pFrag = nullptr;
	Shader* pVert = nullptr;

	Shader* tFrag = nullptr;
	Shader* tVert = nullptr;

	Framebuffer* FrameBuffer = nullptr;

	Camera2D* camera = nullptr;
	ShaderProgram* program = nullptr;
	ShaderProgram* scrProgram = nullptr;
	ShaderProgram* textProgram = nullptr;
	glTexture* tex = nullptr;
	glTexture* bkgrnd = nullptr;
	Renderer2D* renderer = nullptr;
	GameState inState;
	InputManager* input;

	int width = 1024, height = 768;
	struct CameraScale{
		float x, y;
	}scale;
	// Functions
	void HandleInput();
	void DrawGame();
	void UpdateGame();

	bool waterFX;
	bool glitch;
	bool greyScale;
};

