#include "Game.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL\glew.h>
#include <ctime>
float l, r, b, t;
Game::Game()
{
	window = new Window("Game Win : Build Win32 0.1", width, height);
	window->CreateWindow();
	inState = GameState::GAME_RUNNING;
}


Game::~Game(){
	delete scrProgram;
	delete pFrag;
	delete pVert;
	delete fragment;
	delete vertex;
	delete program;
	delete window;
	delete tex;
	delete bkgrnd;
	delete FrameBuffer;
	delete camera;
	delete input;
}
// Very Huge setup
void Game::InitGame(){
	camera = new Camera2D(view, width, height);
	fragment = new Shader(GL_FRAGMENT_SHADER);
	vertex = new Shader(GL_VERTEX_SHADER);
	pFrag = new Shader(GL_FRAGMENT_SHADER);
	pVert = new Shader(GL_VERTEX_SHADER);
	input = new InputManager();
	scrProgram = new ShaderProgram();
	program = new ShaderProgram();
	FrameBuffer = new Framebuffer(width, height);
	pFrag->LoadFromFile("Assests\\Shader\\pp\\frag.glsl"); // Postprocess Fragment
	pVert->LoadFromFile("Assests\\Shader\\pp\\vert.glsl"); // Postprocess Vertex
	fragment->LoadFromFile("Assests\\Shader\\frag.glsl"); // Standard Frag
	vertex->LoadFromFile("Assests\\Shader\\vert.glsl"); // Standard Vertex
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

	// Setting up textures
	tex = new glTexture(); bkgrnd = new glTexture();
	bkgrnd->SetFilter(GL_LINEAR); bkgrnd->SetWrapMode(GL_REPEAT);
	tex->SetFilter(GL_LINEAR);
	tex->SetWrapMode(GL_REPEAT);
	tex->LoadImage("Assests\\Textures\\circle.png");
	bkgrnd->LoadImage("Assests\\Textures\\gradient.png");
	// Setting up renderer
	renderer = new Renderer2D(program);
	renderer->EnableAlpha(true);
	renderer->EnableAntiAliasing(true);
	// Setup orthographic matrix
	scale.x = width; scale.y = height;
	l = 0.; r = width; b = height; t = 0.;
	projection = glm::ortho(l, r, b, t, -1.f, 1.f);
	program->SetUniformMatrix4fv("projection", glm::value_ptr(projection));

	// Setup the balls.
	for (int i = 0; i < 20; i++){
		balls.push_back(DemoBall(glm::vec2(100+i*i, 600), glm::vec2(8*i), glm::vec3(100*i, 100, 200)));
		balls.back().SetBounds(l, r, b, t);
		balls.back().SetVelocity(5 + i-2);
	}
	for (int i = 0; i < 20; i++){
		balls.push_back(DemoBall(glm::vec2(20 + i*i, 600), glm::vec2(8 * i), glm::vec3(2, 100*i, 200)));
		balls.back().SetBounds(l, r, b, t);
		balls.back().SetVelocity(5 + i - 2);
	}
	for (int i = 0; i < 15; i++){
		balls.push_back(DemoBall(glm::vec2(40 + i*i, 600), glm::vec2(8 * i), glm::vec3(2, 2, 40 *i)));
		balls.back().SetBounds(l, r, b, t);
		balls.back().SetVelocity(5 + i - 2);
	}
}
// Run game that condenses all seperate functions into one.
void Game::RunGame(){
	while (inState == GameState::GAME_RUNNING | inState == GameState::GAME_PAUSE){
		HandleInput();
		UpdateGame();
		DrawGame();
	}
}
// Neat little update function
void Game::UpdateGame(){
	view = glm::mat4();
	model = glm::mat4();
	ClockTimer::Tick();
	if (inState != GameState::GAME_PAUSE){
		for (auto &b : balls){
			b.Update(ClockTimer::returnDeltatime(TimeMeasure::TIME_SECONDS));
		}
	}
}

void Game::DrawGame(){
	glViewport(0, 0, 1024, 768);

	// Draw everything here.
	FrameBuffer->Begin();
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.5f, 1.2f, 0.3f, 1.0f);
	camera->SupplyMatrix(view);
	camera->Scale(glm::vec2(scale.x, scale.y)); // camera system.
	view = camera->RetrieveMatrix(); // Call this to transfer matrix.
	program->SetUniformMatrix4fv("view", glm::value_ptr(view));
	program->SetUniformMatrix4fv("model", glm::value_ptr(model));
	for (auto &b : balls){
		renderer->DrawM(b.GetPos(), b.GetSize(), 0, tex, b.GetColor());
	}
	FrameBuffer->End();
	glClear(GL_COLOR_BUFFER_BIT);
	scrProgram->Use();
	// Set all appropriete uniforms
	scrProgram->SetUniform1i("frameBuffer", 0);
	scrProgram->SetUniform1i("waterFX", waterFX);
	scrProgram->SetUniform1i("glitch", glitch);
	scrProgram->SetUniform1i("greyScale", greyScale);
	scrProgram->SetUniform1f("offSet", 0.5f * ClockTimer::returnElaspedTime(TimeMeasure::TIME_SECONDS));
	FrameBuffer->Render();
	scrProgram->Unuse();
	window->Refresh();
}

void Game::HandleInput(){
	input->PollEvents([&](SDL_Event* evnt){
		switch (evnt->type){
		case SDL_QUIT:
			inState = GameState::GAME_QUIT;
			break;
		case SDL_KEYDOWN:
			switch (evnt->key.keysym.sym){
			case SDLK_ESCAPE:
				if (inState != GameState::GAME_PAUSE){
					inState = GameState::GAME_PAUSE;
					printf("BallCount : %d\n", balls.size());
				}
				else{
					inState = GameState::GAME_RUNNING;
				}
				break;
			case SDLK_1:
			case SDLK_z:
				waterFX = !waterFX;
				break;
			case SDLK_2:
			case SDLK_x:
				glitch = !glitch;
				break;
			case SDLK_3:
			case SDLK_c:
				greyScale = !greyScale;
				break;
			}
			break;
		case SDL_KEYUP:
			break;
		default:
			break;
		}
	});
	input->Update();

}