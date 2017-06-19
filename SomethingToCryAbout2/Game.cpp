#include "Game.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL\glew.h>

Game::Game()
{
	window = new Window("Game Window", 1024, 768);
	window->CreateWindow();
	inState = GameState::GAME_RUNNING;
}


Game::~Game(){
	glDeleteVertexArrays(1, &vao);
	delete fragment;
	delete vertex;
	delete program;
	delete window;
	delete tex;
}

void Game::InitGame(){
	glGenVertexArrays(1, &vao);

	VertexBuffer test;
	test.AddVertices(0.0, 0.2);
	test.AddVertices(1.0, -1.0);
	test.AddVertices(-1.0, -1.0);
	test.AddVertices(0.0, 1.0);
	test.AddVertices(1.0, -1.0);
	test.AddVertices(-1.0, -1.0);
	glBindVertexArray(vao);
	
	test.BufferData();
	test.Bind();
	glVertexAttribPointer(0, 2, GL_FLOAT, false, sizeof(float) * 4, (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(float) * 4, (void*)(sizeof(float) * 2));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);
	test.Unbind();
	fragment = new Shader(GL_FRAGMENT_SHADER);
	vertex = new Shader(GL_VERTEX_SHADER);
	program = new ShaderProgram();
	fragment->LoadFromFile("tex.glsl");
	vertex->LoadFromFile("vert.glsl");
	program->AddShader(*vertex);
	program->AddShader(*fragment);
	program->LinkProgram();
	program->DetachShader(*vertex);
	program->DetachShader(*fragment);
	tex = new glTexture();
	tex->SetFilter(GL_LINEAR);
	tex->SetWrapMode(GL_REPEAT);
	tex->LoadImage("test.png");
	program->SetUniform3f("iClr", 100, 1, 155);
}

void Game::RunGame(){
	while (inState == GameState::GAME_RUNNING | inState == GameState::GAME_PAUSE){
		HandleInput();
		DrawGame();
		UpdateGame();
	}
}

void Game::UpdateGame(){

}

void Game::DrawGame(){
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.5f, 1.2f, 0.3f, 1.0f);
	glViewport(0, 0, 1024, 768);
	// Draw everything here.
	program->Use();
	tex->Bind();
	program->SetUniform1i("tex", 0);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);
	tex->Unbind();
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