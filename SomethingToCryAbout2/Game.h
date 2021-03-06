#pragma once
#include <Oats\GameStateEnum.h>
#include <Oats\Window.h>
#include <Oats\InputManager.h>
#include <Oats\ResourceManager.h>
#include <Oats\Shader.h>
#include <Oats\ClockTimer.h>
#include <Oats\VertexBuffer.h>
#include <Oats\glQueryStruct.h>
#include <Oats\VertexArray.h>
#include <Oats\TextRenderer.h>
#include <Oats\glTexture.h>
#include <Oats\Renderer2D.h>
#include <Oats\Camera2D.h>
#include <Oats\Framebuffer.h>
#include "Trigger.h"
#include "Bullet.h"
#include "Entity.h"
#include "Player.h"
#include "Turret.h"
#include "TestAI.h"
#include "LevelLoader.h"
#include <map>
#include "Button.h"
class Game
{
public:
	Game();
	~Game();
	void InitGame();
	void RunGame();
private:
	std::map<std::string, glTexture*> Textures;
	//Math Stuff
	glm::mat4 view = glm::mat4();
	glm::mat4 projection = glm::mat4();
	glm::mat4 model = glm::mat4();
	//
	Window *window = nullptr;

	Shader* waterFrag = nullptr;

	Shader* fragment = nullptr;
	Shader* vertex = nullptr;

	Shader* pFrag = nullptr;
	Shader* pVert = nullptr;

	Shader* tFrag = nullptr;
	Shader* tVert = nullptr;

	Framebuffer* FrameBuffer = nullptr;

	Camera2D* camera = nullptr;
	ShaderProgram* waterProgram = nullptr;
	ShaderProgram* program = nullptr;
	ShaderProgram* scrProgram = nullptr;
	ShaderProgram* textProgram = nullptr;
	Renderer2D* renderer = nullptr;
	
	GameState inState;
	InputManager* input = nullptr;

	TextRenderer* arial = nullptr;
	TextRenderer* smArial = nullptr;
	TextRenderer* cmcSans = nullptr;

	glTexture* wall = nullptr;
	glTexture* enemy = nullptr;
	glTexture* playerT = nullptr;
	glTexture* devTex = nullptr;
	glTexture* bullet = nullptr;
	glTexture* wdFlr = nullptr;
	glTexture* grass = nullptr;
	glTexture* warning = nullptr;
	glTexture* smoothStone = nullptr;
	glTexture* vig = nullptr;
	glTexture* water = nullptr;
	glTexture* turret = nullptr;

	LevelLoader loader[5];
	std::vector<Entity> walls;
	std::vector<TestAI> testAi;
	std::vector<Trigger> triggers;
	std::vector<Bullet> bullets;
	std::vector<Turret> turrets;

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

