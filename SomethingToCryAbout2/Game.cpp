#include "Game.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL\glew.h>
float x = 100;
float y = 100;
float angle = 0;
Game::Game()
{
	window = new Window("Game Win : Build Win32 0.1", 1024, 768);
	window->CreateWindow();
	inState = GameState::GAME_RUNNING;
}


Game::~Game(){
	delete fragment;
	delete vertex;
	delete program;
	delete window;
	delete tex;
}

void Game::InitGame(){
	fragment = new Shader(GL_FRAGMENT_SHADER);
	vertex = new Shader(GL_VERTEX_SHADER);
	program = new ShaderProgram();
	fragment->LoadFromFile("Assests\\Shader\\frag.glsl");
	vertex->LoadFromFile("Assests\\Shader\\vert.glsl");
	program->AddShader(*vertex);
	program->AddShader(*fragment);
	program->LinkProgram();
	program->DetachShader(*vertex);
	program->DetachShader(*fragment);
	tex = new glTexture();
	tex->SetFilter(GL_LINEAR);
	tex->SetWrapMode(GL_REPEAT);
	tex->LoadImage("Assests\\Textures\\circle.png");
	renderer = new Renderer2D(program);
	renderer->EnableAlpha(true);
	renderer->EnableAntiAliasing(true);
	float l, r, b, t;
	l = 0.; r = 1024.; b = 0.; t = 768.;
	projection = glm::ortho(l, r, b, t, -1.f, 1.f);
	program->SetUniformMatrix4fv("projection", glm::value_ptr(projection));
}

void Game::RunGame(){
	while (inState == GameState::GAME_RUNNING | inState == GameState::GAME_PAUSE){
		HandleInput();
		UpdateGame();
		DrawGame();
	}
}

void Game::UpdateGame(){
	view = glm::mat4();
	model = glm::mat4();
}

void Game::DrawGame(){
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.5f, 1.2f, 0.3f, 1.0f);
	glViewport(0, 0, 1024, 768);

	// Draw everything here.
	program->SetUniformMatrix4fv("model", glm::value_ptr(model));
	program->Use();
	angle += 0.2;
	renderer->DrawM(glm::vec2(x, y), glm::vec2(150, 150), angle, tex, glm::vec3(155, 10, 255));
	program->SetUniformMatrix4fv("view", glm::value_ptr(view));
	window->Refresh();
}

void Game::HandleInput(){
	while (SDL_PollEvent(&window->event)){
		switch (window->event.type){
		case SDL_QUIT:
			inState = GameState::GAME_QUIT;
			break;
		case SDL_KEYDOWN:
			break;
		case SDL_KEYUP:
			break;
		}
	}
}