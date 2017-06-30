#include "Game.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Paddle.h"
#include "Bullet.h"
#include "Entity.h"
#include "Player.h"
#include "TestAI.h"
#include <Oats\ResourceManager.h>
#include <cmath>
#include <GL\glew.h>
#include <ctime>
int mx;
int my;

Player player(glm::vec2(360), glm::vec2(20), glm::vec3(255), 100, "test", false);
TestAI one(glm::vec2(380), glm::vec2(20), glm::vec3(255), 100, "ai", true);

std::vector<Entity> walls;
std::vector<TestAI> testAi;
std::vector<Bullet> bullets;

glQueryInfo info;
glTexture* wall;
glTexture* playerT;
glTexture* devTex;
glTexture* bullet;
std::string sideCollided = "Nothing";
Game::Game()
{
	window = new Window("Something To Cry About : OpenGL Version Alpha", width, height);
	window->CreateWindow();
	info = QueryInformation();
	printf("OpenGL Vendor : %s \nOpenGL Renderer: %s\n", info.vendor, info.renderer);
	printf("OpenGL Version : %s \nOpenGL-SL Version : %s\n", info.version.legacy, info.glsl_lang_version);
	printf("OpenGL Supported Extensions # : %d\n", info.ext_support_num);
	printf("OpenGL Extensions Supported are :\n");
	CheckExtension("GL_EXT_direct_state_access", info);
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
	delete bullet;
	delete playerT;
}
// Very Huge setup

std::string TextureListNames[] = {
	"wall-dev", "dev", "player"
};

void Game::InitGame(){
	// Setup the map here
	bullet = new glTexture();
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
	bullet->SetFilter(GL_LINEAR);
	bullet->SetWrapMode(GL_REPEAT);
	bullet->LoadImage("Assests\\Textures\\bullet.png");
	wall->LoadImage("Assests\\Textures\\dvColBox.png");
	devTex->LoadImage("Assests\\Textures\\dvBox.png");

	Textures.insert(std::pair<std::string, glTexture*>(TextureListNames[0], wall)); // put all textures in a map;
	Textures.insert(std::pair<std::string, glTexture*>(TextureListNames[1], devTex));
	Textures.insert(std::pair<std::string, glTexture*>(TextureListNames[2], playerT));
	Textures.insert(std::pair<std::string, glTexture*>("bullet", bullet));
	camera = new Camera2D(view, width, height, 4, 0.5);
	camera->SetScale(1);
	/*
	 * Setting up the shaders for the
	 * game
	 */
	fragment = new Shader(GL_FRAGMENT_SHADER); // standard sprite shader
	vertex = new Shader(GL_VERTEX_SHADER); // standard vertex sprite shader
	pFrag = new Shader(GL_FRAGMENT_SHADER); // postprocessing frag
	pVert = new Shader(GL_VERTEX_SHADER); // postprocessing vert
	tFrag = new Shader(GL_FRAGMENT_SHADER); // text frag
	tVert = new Shader(GL_VERTEX_SHADER); // text vert
	input = new InputManager(); // InputManager
	textProgram = new ShaderProgram(); // Text Shader Program
	scrProgram = new ShaderProgram(); // Screen Shader Program
	program = new ShaderProgram(); // Default Shader Program

	FrameBuffer = new Framebuffer(width, height);
	
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

	walls.push_back(Entity(glm::vec2(400), glm::vec2(200), glm::vec3(255), 100, "dev", true));
	walls.push_back(Entity(glm::vec2(200), glm::vec2(100), glm::vec3(255), 100, "wall-dev", true));
	walls.push_back(Entity(glm::vec2(0), glm::vec2(30, 768), glm::vec3(0), 100, "Boundary", true));
	walls.push_back(Entity(glm::vec2(1024, 0), glm::vec2(30, 768), glm::vec3(0), 100, "Boundary", true));
	walls.push_back(Entity(glm::vec2(0), glm::vec2(1024, 30), glm::vec3(0), 100, "Boundary", true));
	walls.push_back(Entity(glm::vec2(0, 768), glm::vec2(1024, 30), glm::vec3(0), 100, "Boundary", true));
	one.SetSpeed(120, 120);

	testAi.push_back(one);
	testAi.push_back(TestAI(glm::vec2(200, 100), glm::vec2(20), glm::vec3(255), 100, "1oddity", true));
	testAi.push_back(TestAI(glm::vec2(100, 200), glm::vec2(20), glm::vec3(255), 100, "bobbity", true));
	testAi.push_back(TestAI(glm::vec2(200, 500), glm::vec2(50), glm::vec3(255), 100, "oddity", true));

	for (auto & a : testAi){
		a.SetSpeed(120, 120);
	}
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
		for (auto & ai : testAi){
			ai.Update(ClockTimer::returnDeltatime(TimeMeasure::TIME_SECONDS));
		}
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
			for (auto & proj : bullets){
				if (proj.AABBCollide(wall)){
					proj.SetActive(false);
				}
			}
			for (auto &ai : testAi){
				if (ai.AABBCollide(wall)){
					ai.SideCollide(wall, ClockTimer::returnDeltatime(TimeMeasure::TIME_SECONDS));
				}
			}
		}
		for (auto & proj : bullets){
			proj.Update(ClockTimer::returnDeltatime(TimeMeasure::TIME_SECONDS));
			if (!proj.isActive()){
				bullets.pop_back(); // Change this
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
	camera->Identity();
	camera->Translate(glm::vec2((-player.GetPosition().x*camera->GetScale() + width/2), (-player.GetPosition().y*camera->GetScale() + height/2)));
	camera->Scale(glm::vec2(scale.x, scale.y)); // camera system.
	view = camera->RetrieveMatrix(); // Call this to transfer matrix.
	program->SetUniformMatrix4fv("view", glm::value_ptr(view));
	if (inState == GameState::GAME_MENU){
	}
	if (inState == GameState::GAME_RUNNING){
		renderer->Begin(*Textures["wall-dev"], glm::vec3(255));
		// walls
		for (auto& wll : walls){
			// Compare the name of these things to all possible wall name values
			if (wll.GetName() == "wall-dev" || wll.GetName() == "dev")
				renderer->Draw(wll.GetPosition(), wll.GetSize(), 0);
			else{
				renderer->SetColor(wll.GetColor());
				renderer->DrawRect(wll.GetPosition(), wll.GetSize(), 0);
			}
			}
		renderer->End(*Textures["wall-dev"]);
		renderer->Begin(*Textures["player"], glm::vec3(255));
		for (auto & ai : testAi){
			renderer->Draw(ai.GetPosition(), ai.GetSize(), ai.GetAngle());
		}
		//Everything else
		renderer->Draw(player.GetPosition(), player.GetSize(), player.GetAngle());
		renderer->End(*Textures["player"]);
		renderer->Begin(*Textures["bullet"], glm::vec3(255));
		for (auto & proj : bullets){
			renderer->Draw(proj.GetPosition(), proj.GetSize(), proj.GetAngle());
		}
		renderer->End(*Textures["bullet"]);
	}

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
#ifdef DEBUG_HUD
	smArial->Render("Player Angle : " + std::to_string(player.GetAngle()), glm::vec2(10, 190), 1, glm::vec3(1, 0, 0));
	smArial->Render("Last Collided With : " + sideCollided, glm::vec2(10, 170), 1, glm::vec3(1, 0, 0));
	smArial->Render("Camera Zoom : " + std::to_string(camera->GetScale()), glm::vec2(10, 150), 1, glm::vec3(1, 0, 0 ));
	smArial->Render("OpenGL Vendor: " + std::string(reinterpret_cast<const char*>(info.vendor)), glm::vec2(10, 20), 1, glm::vec3(255));
	smArial->Render("OpenGL Version: " + std::string(reinterpret_cast<const char*>(info.version.legacy.gl_api_version)), glm::vec2(250, 20), 1, glm::vec3(255));
	smArial->Render("OpenGL-SL Version : " + std::string(reinterpret_cast<const char*>(info.glsl_lang_version)), glm::vec2(10, 40), 1, glm::vec3(255));
	smArial->Render("OpenGL Renderer : " + std::string(reinterpret_cast<const char*>(info.renderer)), glm::vec2(10, 90), 1, glm::vec3(255));
	smArial->Render("OpenGL Supported Extensions #: " + std::to_string(info.ext_support_num), glm::vec2(10, 60), 1, glm::vec3(255));
#endif 
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
			case SDLK_1:
				glitch = !glitch;
				break;
			case SDLK_2:
				greyScale = !greyScale;
				break;
			case SDLK_3:
				waterFX = !waterFX;
				break;
			case SDLK_SPACE:
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
	input->isKeyPressed(SDL_SCANCODE_SPACE, [&](){
		if (bullets.size() != MAX_PROJECTILES){
			bullets.push_back(Bullet(glm::vec2(player.GetPosition()), glm::vec2(10), glm::vec3(255), 10, "bullet", false, 120));
			bullets.back().SetAngle(player.GetAngle());
			bullets.back().SetSpeed(350, 350);
		}
	});
	// atan2(input->GetMouseY() - test.GetPosition().y, input->GetMouseX() - test.GetPosition().x);
}
