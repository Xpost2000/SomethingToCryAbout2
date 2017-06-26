#include "Game.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Paddle.h"
#include "Entity.h"
#include "Player.h"
#include <Oats\ResourceManager.h>
#include <cmath>
#include <GL\glew.h>
#include <ctime>
int mx;
int my;

Player player(glm::vec2(360), glm::vec2(20), glm::vec3(255), 100, "test", false);


std::vector<Entity> walls;
glQueryInfo info;
glTexture* wall;
glTexture* playerT;
glTexture* devTex;
std::string sideCollided = "Nothing";
Game::Game()
{
	window = new Window("Something To Cry About : OpenGL Version Alpha", width, height);
	window->CreateWindow();
	info = QueryInformation();
	printf("OpenGL Vendor : %s \nOpenGL Renderer: %s\n", info.vendor, info.renderer);
	printf("OpenGL Version : %s \nOpenGL-SL Version : %s\n", info.version.legacy, info.glsl_lang_version);
//	printf("OpenGL Extensions Supported : %s\n", info.ext_support_num);
	inState = GameState::GAME_RUNNING;
}


Game::~Game(){
	delete scrProgram;
	delete pFrag;
	delete pVert;
	delete fragment;
	delete vertex;
	delete program;
	delete smArial;
	delete arial;
	delete cmcSans;
	delete textProgram;
	delete window;
	delete FrameBuffer;
	delete camera;
	delete tFrag;
	delete tVert;
	delete input;
	delete wall;
	delete devTex;
	delete playerT;
}
// Very Huge setup

std::string TextureListNames[] = {
	"wall-dev", "dev", "player"
};

void Game::InitGame(){
	// Setup the map here
	
	wall = new glTexture();
	devTex = new glTexture();
	playerT = new glTexture();
	wall->SetFilter(GL_LINEAR);
	devTex->SetFilter(GL_LINEAR);
	wall->SetWrapMode(GL_REPEAT);
	devTex->SetWrapMode(GL_REPEAT);
	playerT->SetFilter(GL_LINEAR);
	playerT->SetWrapMode(GL_REPEAT);
	playerT->LoadImage("Assests\\Textures\\player.png");
	wall->LoadImage("Assests\\Textures\\dvColBox.png");
	devTex->LoadImage("Assests\\Textures\\dvBox.png");

	Textures.insert(std::pair<std::string, glTexture*>(TextureListNames[0], wall)); // put all textures in a map;
	Textures.insert(std::pair<std::string, glTexture*>(TextureListNames[1], devTex));
	Textures.insert(std::pair<std::string, glTexture*>(TextureListNames[2], playerT));

	camera = new Camera2D(view, width, height, 4, 0.5);
	camera->SetScale(1);
	fragment = new Shader(GL_FRAGMENT_SHADER);
	vertex = new Shader(GL_VERTEX_SHADER);
	pFrag = new Shader(GL_FRAGMENT_SHADER);
	pVert = new Shader(GL_VERTEX_SHADER);
	tFrag = new Shader(GL_FRAGMENT_SHADER);
	tVert = new Shader(GL_VERTEX_SHADER);
	input = new InputManager();
	textProgram = new ShaderProgram();
	scrProgram = new ShaderProgram();
	program = new ShaderProgram();

	FrameBuffer = new Framebuffer(width, height);
	// TODO incorporate SPR-V loading
	pFrag->LoadFromFile("Assests\\Shader\\pp\\frag.glsl"); // Postprocess Fragment
	pVert->LoadFromFile("Assests\\Shader\\pp\\vert.glsl"); // Postprocess Vertex
	fragment->LoadFromFile("Assests\\Shader\\frag.glsl"); // Standard Frag
	vertex->LoadFromFile("Assests\\Shader\\vert.glsl"); // Standard Vertex
	tFrag->LoadFromFile("Assests\\Shader\\text\\textFrag.glsl");
	tVert->LoadFromFile("Assests\\Shader\\text\\textVert.glsl");

	program->AddShader(*vertex); // Adding Shaders for compilation
	program->AddShader(*fragment);
	program->LinkProgram(); // Link shaders
	program->DetachShader(*vertex);
	program->DetachShader(*fragment); // Detach Shaders

	// Framebuffer / Postprocessing program
	scrProgram->AddShader(*pFrag);
	scrProgram->AddShader(*pVert);
	scrProgram->LinkProgram();
	scrProgram->DetachShader(*pFrag);
	scrProgram->DetachShader(*pVert);

	textProgram->AddShader(*tFrag);
	textProgram->AddShader(*tVert);
	textProgram->LinkProgram();
	textProgram->DetachShader(*tFrag);
	textProgram->DetachShader(*tVert);
	// Setting up textures
	// Setting up renderer
	renderer = new Renderer2D(program);
	renderer->EnableAlpha(true);
	renderer->EnableAntiAliasing(true);
	// Setup orthographic matrix
	scale.x = width; scale.y = height;
	float l = 0.; float r = width; float b = height; float t = 0.;
	projection = glm::ortho(l, r, b, t, -1.f, 1.f);
	program->SetUniformMatrix4fv("projection", glm::value_ptr(projection));
	textProgram->SetUniformMatrix4fv("proj", glm::value_ptr(projection));
	arial = new TextRenderer(textProgram);
	cmcSans = new TextRenderer(textProgram);
	smArial = new TextRenderer(textProgram);
	arial->LoadFont("Assests\\Font\\arial.ttf", 48);
	cmcSans->LoadFont("Assests\\Font\\cmc.ttf", 72);
	smArial->LoadFont("Assests\\Font\\arial.ttf", 14);
	player.SetSpeed(120, 120);
	player.SetAngle(360);
	view = glm::mat4();
	//camera->SupplyMatrix(view);
	walls.push_back(Entity(glm::vec2(400), glm::vec2(200), glm::vec3(255), 100, "dev", true));
	walls.push_back(Entity(glm::vec2(200), glm::vec2(100), glm::vec3(255), 100, "wall-dev", true));
	walls.push_back(Entity(glm::vec2(0), glm::vec2(30, 768), glm::vec3(0), 100, "Boundary", true));
	walls.push_back(Entity(glm::vec2(1024, 0), glm::vec2(30, 768), glm::vec3(0), 100, "Boundary", true));
	walls.push_back(Entity(glm::vec2(0), glm::vec2(1024, 30), glm::vec3(0), 100, "Boundary", true));
	walls.push_back(Entity(glm::vec2(0, 768), glm::vec2(1024, 30), glm::vec3(0), 100, "Boundary", true));
}
// Run game that condenses all seperate functions into one.
void Game::RunGame(){
	while (inState != GameState::GAME_QUIT){
		HandleInput();
		UpdateGame();
		DrawGame();
	}
}
// Neat little update function
void Game::UpdateGame(){
	// Simulate Everything here.
	if (inState != GameState::GAME_PAUSE){
		//SDL_SetRelativeMouseMode(SDL_TRUE);
		mx = input->GetMouseX();
		my = input->GetMouseY();
		player.Update(ClockTimer::returnDeltatime(TimeMeasure::TIME_SECONDS), input, camera);
	}
	else{
	//	SDL_SetRelativeMouseMode(SDL_FALSE);
	}
	model = glm::mat4();
	ClockTimer::Tick();
	if (inState == GameState::GAME_RUNNING){
		for (auto& wall : walls){
			if(player.AABBCollide(wall)){
				player.SideCollide(wall, ClockTimer::returnDeltatime(TimeMeasure::TIME_SECONDS));
				sideCollided = wall.GetName();
			}
		}
	}
}

void Game::DrawGame(){
	glViewport(0, 0, 1024, 768);

	// Draw everything here.

	FrameBuffer->Begin();
	//
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.f, 0.2f, .3f, 1.0f);
	
	//test.GetPosition().x + test.GetSize().x / 2) - width / 2., (test.GetPosition().y + test.GetSize().y / 2) - height / 2.)
	program->Use();
	camera->Identity();
	camera->Translate(glm::vec2((-player.GetPosition().x*camera->GetScale() + width/2), (-player.GetPosition().y*camera->GetScale() + height/2)));
	camera->Scale(glm::vec2(scale.x, scale.y)); // camera system.
	view = camera->RetrieveMatrix(); // Call this to transfer matrix.
	program->SetUniformMatrix4fv("view", glm::value_ptr(view));
	if (inState == GameState::GAME_MENU){
	}
	if (inState == GameState::GAME_RUNNING){
		// walls
		for (auto& wll : walls){
			// Compare the name of these things to all possible wall name values
			if (wll.GetName() == "wall-dev" || wll.GetName() == "dev")
				renderer->Draw(wll.GetPosition(), wll.GetSize(), 0, *Textures[wll.GetName()]);
			else
				renderer->Draw(wll.GetPosition(), wll.GetSize(), 0, wll.GetColor());
		}
		//Everything else
		renderer->Draw(player.GetPosition(), player.GetSize(), player.GetAngle(), *Textures["player"]);
	}
	program->Unuse();
	FrameBuffer->End();

	glClear(GL_COLOR_BUFFER_BIT);
	scrProgram->SetUniform1i("frameBuffer", 0);
	scrProgram->SetUniform1i("waterFX", waterFX);
	scrProgram->SetUniform1i("glitch", glitch);
	scrProgram->SetUniform1i("greyScale", greyScale);
	scrProgram->SetUniform1f("offSet", 0.5f * ClockTimer::returnElaspedTime(TimeMeasure::TIME_SECONDS));
	scrProgram->Use();
	FrameBuffer->Render();
	scrProgram->Unuse();
	smArial->Render("Player Angle : " + std::to_string(player.GetAngle()), glm::vec2(10, 190), 1, glm::vec3(1, 0, 0));
	smArial->Render("Last Collided With : " + sideCollided, glm::vec2(10, 170), 1, glm::vec3(1, 0, 0));
	smArial->Render("Camera Zoom : " + std::to_string(camera->GetScale()), glm::vec2(10, 150), 1, glm::vec3(1, 0, 0 ));
	smArial->Render("OpenGL Vendor: " + std::string(reinterpret_cast<const char*>(info.vendor)), glm::vec2(10, 20), 1, glm::vec3(255));
	smArial->Render("OpenGL Version: " + std::string(reinterpret_cast<const char*>(info.version.legacy.gl_api_version)), glm::vec2(250, 20), 1, glm::vec3(255));
	smArial->Render("OpenGL-SL Version : " + std::string(reinterpret_cast<const char*>(info.glsl_lang_version)), glm::vec2(10, 40), 1, glm::vec3(255));
	smArial->Render("OpenGL Renderer : " + std::string(reinterpret_cast<const char*>(info.renderer)), glm::vec2(10, 90), 1, glm::vec3(255));
	
	if (inState == GameState::GAME_PAUSE || inState == GameState::GAME_MENU){
	}
	if (inState == GameState::GAME_RUNNING){
	}
	window->Refresh();
}

void Game::HandleInput(){
	input->Update();
	input->PollEvents([&](SDL_Event* evnt){
		switch (evnt->type){
		case SDL_QUIT:
			inState = GameState::GAME_QUIT;
			break;
		case SDL_KEYDOWN:
			switch (evnt->key.keysym.sym){
			case SDLK_ESCAPE:
				if (inState != GameState::GAME_PAUSE)
					inState = GameState::GAME_PAUSE; else{
					inState = GameState::GAME_RUNNING;
				}
				break;
			}
			break;
		case SDL_KEYUP:
			break;
		case SDL_MOUSEBUTTONDOWN:
			break;
		default:
			break;
		}
	});
	// atan2(input->GetMouseY() - test.GetPosition().y, input->GetMouseX() - test.GetPosition().x);
}