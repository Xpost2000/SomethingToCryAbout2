#include "Game.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Paddle.h"
#include <GL\glew.h>
#include <ctime>
int mx;
int my;
int score[2];
float animatedTextX = 0.0;
Ball ball(glm::vec2(1024/2 - 20, 768 / 2 - 20), glm::vec2(20), 300 , 47);
Paddle a(glm::vec2( 40, 400), glm::vec2(10, 100));
Paddle b(glm::vec2(1024 - 40, 400), glm::vec2(10, 100));
struct DemoCoords{
	float y1 = 400; // P1 Demo
	float y2 = 400; // P2 Demo
}set;

std::string specialFx = "None";
glm::vec3 textColor = { 0, 0, 0 };
Button play(glm::vec2(382, 680), glm::vec2(340, 60), glm::vec3(255), glm::vec3(0), "Play Game");
glQueryInfo info;
Game::Game()
{
	window = new Window("Game Win : Build Win32 0.1", width, height);
	window->CreateWindow();
	info = QueryInformation();
	printf("OpenGL Vendor : %s \nOpenGL Renderer: %s\n", info.vendor, info.renderer);
	printf("OpenGL Version : %s \nOpenGL-SL Version : %s\n", info.version.legacy, info.glsl_lang_version);
//	printf("OpenGL Extensions Supported : %s\n", info.ext_support_num);
	inState = GameState::GAME_MENU;
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
}
// Very Huge setup
void Game::InitGame(){
	play.SetID(1);
	camera = new Camera2D(view, width, height);
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
	mx = input->GetMouseX();
	my = input->GetMouseY();
	view = glm::mat4();
	model = glm::mat4();
	ClockTimer::Tick();
	set.y1 += cos(ClockTimer::returnElaspedTime(TimeMeasure::TIME_SECONDS) / 3);
	set.y2 += cos(ClockTimer::returnElaspedTime(TimeMeasure::TIME_SECONDS) * 0.2);
	glitch = true;
	if (inState == GameState::GAME_RUNNING){
		glitch = false;
		if (animatedTextX > 1024)
		ball.Update(ClockTimer::returnDeltatime(TimeMeasure::TIME_SECONDS));
		else{
		//	animatedTextX += cos(ClockTimer::returnElaspedTime(TimeMeasure::TIME_SECONDS) / 10)*6;
			animatedTextX += 220 * ClockTimer::returnDeltatime(TimeMeasure::TIME_SECONDS);
		}
		if (a.Collide(ball)){
			ball.InvertVX();
		}
		if (b.Collide(ball)){
			ball.InvertVX();
		}
		if (ball.pos.x + ball.size.x > 1024){
			score[0] ++;
			animatedTextX = 0;
			a = Paddle(glm::vec2(40, 400), glm::vec2(10, 100));
			b = Paddle(glm::vec2(1024 - 40, 400), glm::vec2(10, 100));
			ball = Ball(glm::vec2(1024 / 2 - 20, 768 / 2 - 20), glm::vec2(20), 300, 47);
		}
		if (ball.pos.x < 0){
			score[1] ++;
			animatedTextX = 0;
			a = Paddle(glm::vec2(40, 400), glm::vec2(10, 100));
			b = Paddle(glm::vec2(1024 - 40, 400), glm::vec2(10, 100));
			ball = Ball(glm::vec2(1024 / 2 - 20, 768 / 2 - 20), glm::vec2(20), 300, 47);
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
	camera->SupplyMatrix(view);
	camera->Scale(glm::vec2(scale.x, scale.y)); // camera system.
	view = camera->RetrieveMatrix(); // Call this to transfer matrix.
	program->SetUniformMatrix4fv("view", glm::value_ptr(view));
	if (inState == GameState::GAME_MENU){
		renderer->Draw(glm::vec2(40, set.y1), glm::vec2(10, 100), 0, glm::vec3(255));
		renderer->Draw(glm::vec2(1024-40, set.y2), glm::vec2(10, 100), 0, glm::vec3(255));
		renderer->Draw(glm::vec2(set.y1, set.y2), glm::vec2(30), 0, glm::vec3(255));
	}
	if (inState == GameState::GAME_RUNNING){

		renderer->Draw(a.GetPos(), a.GetSize(), 0);
		renderer->Draw(b.GetPos(), b.GetSize(), 0);
		renderer->Draw(ball.GetPos(), ball.GetSize(), 0);
		arial->Render("Player 1 : " + std::to_string(score[0]), glm::vec2(30, 700), 1, glm::vec3( 0, 1, 0));
		arial->Render("Player 2 : " + std::to_string(score[1]), glm::vec2(700, 700), 1, glm::vec3(0, 1, 0));
		renderer->Draw(glm::vec2(animatedTextX, 768 / 2), glm::vec2(1024, 80), 0, glm::vec3(0));
		cmcSans->Render("Game Time!", glm::vec2(animatedTextX, 768 / 2), 1, glm::vec3(1, 0, 0));
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
	smArial->Render("OpenGL Vendor: " + std::string(reinterpret_cast<const char*>(info.vendor)), glm::vec2(10, 20), 1, glm::vec3(255));
	smArial->Render("OpenGL Version: " + std::string(reinterpret_cast<const char*>(info.version.legacy.gl_api_version)), glm::vec2(250, 20), 1, glm::vec3(255));
	smArial->Render("OpenGL-SL Version : " + std::string(reinterpret_cast<const char*>(info.glsl_lang_version)), glm::vec2(10, 40), 1, glm::vec3(255));
	smArial->Render("OpenGL Renderer : " + std::string(reinterpret_cast<const char*>(info.renderer)), glm::vec2(10, 90), 1, glm::vec3(255));
	
	// Drawing a button like this
	if (inState == GameState::GAME_PAUSE || inState == GameState::GAME_MENU){
		cmcSans->Render("Oats PONG!", glm::vec2(340, 100), 1., glm::vec3(1, 0, 0));
		arial->Render("Oats FW Test", glm::vec2(340, 180), 0.66, glm::vec3(0, 1, 0));
		renderer->Draw(play.GetLoc(), play.GetSize(), 0, play.GetColor());
		arial->Render(play.GetString(), play.GetTextLoc(), 1, play.GetTextColor());
		animatedTextX = 0;
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
				inState = GameState::GAME_MENU;
				break;
			}
			break;
		case SDL_KEYUP:
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (inState == GameState::GAME_MENU){
				if (play.IsInBounds(mx, my)){
					SDL_Delay(500);
					inState = GameState::GAME_RUNNING;
				}
			}
			break;
		default:
			break;
		}
	});
	if (animatedTextX > 1024){
		input->isKeyPressed(SDL_SCANCODE_W, [&](){
			a.MoveUp(ClockTimer::returnDeltatime(TimeMeasure::TIME_SECONDS));
		});
		input->isKeyPressed(SDL_SCANCODE_S, [&](){
			a.MoveDown(ClockTimer::returnDeltatime(TimeMeasure::TIME_SECONDS));
		});
		input->isKeyPressed(SDL_SCANCODE_UP, [&](){
			b.MoveUp(ClockTimer::returnDeltatime(TimeMeasure::TIME_SECONDS));
		});
		input->isKeyPressed(SDL_SCANCODE_DOWN, [&](){
			b.MoveDown(ClockTimer::returnDeltatime(TimeMeasure::TIME_SECONDS));
		});
	}
}