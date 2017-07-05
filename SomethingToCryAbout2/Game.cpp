#include "Game.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Paddle.h"

#include <Oats\ResourceManager.h>

#include <cmath>
#include <ctime>
int mx;
int my;
const float playerSpeed = 230.f;

Player player(glm::vec2(360), glm::vec2(STANDARD_SIZE), glm::vec3(255), 100, "Player", false);

glQueryInfo info;
float factor = 1.88;
Game::Game()
{
	window = new Window("Something To Cry About : OpenGL Version Alpha", width, height);

	window->CreateWindow();
	info = QueryInformation();
	printf("OpenGL Vendor : %s \nOpenGL Renderer: %s\n", info.vendor, info.renderer);
	printf("OpenGL Version : %s \nOpenGL-SL Version : %s\n", info.version.legacy, info.glsl_lang_version);
	printf("OpenGL Supported Extensions # : %d\n", info.ext_support_num);
	printf("OpenGL Extensions Supported are :\n");
	PrintSupportedExtensions(info);

	inState = GameState::GAME_RUNNING;
}


Game::~Game(){
	delete scrProgram;
	scrProgram = nullptr;
	delete pFrag;
	pFrag = nullptr;
	delete pVert;
	pVert = nullptr;
	delete fragment;
	fragment = nullptr;
	delete vertex;
	vertex = nullptr;
	delete program;
	program = nullptr;
	delete smArial;
	smArial = nullptr;
	delete arial;
	arial = nullptr;
	delete cmcSans;
	cmcSans = nullptr;
	delete textProgram;
	textProgram = nullptr;
	delete window;
	window = nullptr;
	delete warning;
	warning = nullptr;
	delete FrameBuffer;
	FrameBuffer = nullptr;
	delete camera;
	camera = nullptr;
	delete tFrag;
	tFrag = nullptr;
	delete tVert;
	tVert = nullptr;
	delete input;
	input = nullptr;
	delete wall;
	wall = nullptr;
	delete smoothStone;
	smoothStone = nullptr;
	delete waterFrag;
	waterFrag = nullptr;
	delete devTex;
	devTex = nullptr;
	delete bullet;
	bullet = nullptr;
	delete playerT;
	playerT = nullptr;
	delete water;
	water = nullptr;
	delete grass;
	grass = nullptr;
	delete vig;
	vig = nullptr;
	delete wdFlr;
	wdFlr = nullptr;
	delete turret;
	turret = nullptr;
}

void Game::InitGame(){
	// Setup the map here
	loader.LoadLevel("Assests\\test.txt");
	loader.ProcessLevel(walls, testAi, triggers, turrets,player);
	bullet = new glTexture();
	warning = new glTexture();
	wall = new glTexture();
	wdFlr = new glTexture();
	devTex = new glTexture();
	playerT = new glTexture();
	smoothStone = new glTexture();
	vig = new glTexture();
	turret = new glTexture();
	grass = new glTexture();
	water = new glTexture();

	turret->SetFilter(GL_LINEAR);
	turret->SetWrapMode(GL_REPEAT);
	turret->LoadImage("Assests\\Textures\\turret.png");
	warning->SetFilter(GL_LINEAR);
	warning->SetWrapMode(GL_REPEAT);
	warning->LoadImage("Assests\\Textures\\warning.png");
	grass->SetFilter(GL_NEAREST);
	grass->SetWrapMode(GL_CLAMP_TO_BORDER);
	grass->LoadImage("Assests\\Textures\\grass.png");
	vig->SetFilter(GL_LINEAR);
	vig->SetWrapMode(GL_CLAMP_TO_BORDER);
	vig->LoadImage("Assests\\Textures\\vignette.png");
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
	wdFlr->SetFilter(GL_LINEAR);
	wdFlr->SetWrapMode(GL_REPEAT);
	wdFlr->LoadImage("Assests\\Textures\\wood_floor.png");
	smoothStone->SetFilter(GL_LINEAR);
	smoothStone->SetWrapMode(GL_REPEAT);
	smoothStone->LoadImage("Assests\\Textures\\smooth_stone.png");
	water->SetFilter(GL_LINEAR);
	water->SetWrapMode(GL_REPEAT);
	water->LoadImage("Assests\\Textures\\water.png");
	Textures.insert(std::pair<std::string, glTexture*>("wall-dev", wall)); // put all textures in a map;
	Textures.insert(std::pair<std::string, glTexture*>("dev", devTex));
	Textures.insert(std::pair<std::string, glTexture*>("player", playerT));
	Textures.insert(std::pair<std::string, glTexture*>("bullet", bullet));
	Textures.insert(std::pair<std::string, glTexture*>("wood-floor", wdFlr));
	Textures.insert(std::pair<std::string, glTexture*>("smooth-stone", smoothStone));
	Textures.insert(std::pair < std::string, glTexture*>("water", water));
	Textures.insert(std::pair<std::string, glTexture*>("vig", vig));
	Textures.insert(std::pair<std::string, glTexture*>("warning", warning));
	Textures.insert(std::pair<std::string, glTexture*>("grass", grass));
	Textures.insert(std::pair<std::string, glTexture*>("turret", turret));
	camera = new Camera2D(view, width, height, 2, 1.23);
	camera->SetScale(1.23);
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
	waterFrag = new Shader(GL_FRAGMENT_SHADER);
	input = new InputManager(); // InputManager
	waterProgram = new ShaderProgram();
	textProgram = new ShaderProgram(); // Text Shader Program
	scrProgram = new ShaderProgram(); // Screen Shader Program
	program = new ShaderProgram(); // Default Shader Program

	FrameBuffer = new Framebuffer(width, height);
	
	pFrag->LoadFromFile("Assests\\Shader\\pp\\frag.glsl"); // Postprocess Fragment
	pVert->LoadFromFile("Assests\\Shader\\pp\\vert.glsl"); // Postprocess Vertex
	fragment->LoadFromFile("Assests\\Shader\\frag.glsl"); // Standard Frag
	vertex->LoadFromFile("Assests\\Shader\\vert.glsl"); tFrag->LoadFromFile("Assests\\Shader\\text\\textFrag.glsl");tVert->LoadFromFile("Assests\\Shader\\text\\textVert.glsl");
	waterFrag->LoadFromFile("Assests\\Shader\\wFrag.glsl");
	waterProgram->AddShader(*waterFrag);
	waterProgram->AddShader(*vertex);
	waterProgram->LinkProgram();
	program->AddShader(*vertex); // Adding Shaders for compilation
	program->AddShader(*fragment);
	program->LinkProgram(); program->DetachShader(*vertex);	program->DetachShader(*fragment); // Detach Shaders

	// Framebuffer / Postprocessing program
	scrProgram->AddShader(*pFrag);
	scrProgram->AddShader(*pVert);
	scrProgram->LinkProgram();scrProgram->DetachShader(*pFrag);scrProgram->DetachShader(*pVert);

	textProgram->AddShader(*tFrag);
	textProgram->AddShader(*tVert);
	textProgram->LinkProgram();textProgram->DetachShader(*tFrag);textProgram->DetachShader(*tVert);
	// Setting up textures
	// Setting up renderer
	renderer = new Renderer2D(program);
	renderer->EnableAlpha(true);
	// Setup orthographic matrix
	scale = { width, height };
	projection = glm::ortho(0.f, (float)width, (float)height, 0.f, -1.f, 1.f);
	program->SetUniformMatrix4fv("projection", glm::value_ptr(projection));
	textProgram->SetUniformMatrix4fv("proj", glm::value_ptr(projection));
	arial = new TextRenderer(textProgram); cmcSans = new TextRenderer(textProgram);smArial = new TextRenderer(textProgram);
	arial->LoadFont("Assests\\Font\\arial.ttf", 48);cmcSans->LoadFont("Assests\\Font\\cmc.ttf", 72);smArial->LoadFont("Assests\\Font\\arial.ttf", 14);
	player.SetSpeed(240, 240);player.SetAngle(360);player.SetFire(true);
	scrProgram->SetUniform1i("frameBuffer", 0);
	for (auto & a : testAi){a.SetSpeed(120, 120);}
}

// Run game that condenses all seperate functions into one.
void Game::RunGame(){
	while (inState != GameState::GAME_QUIT && !window->GetShouldClose() && player.isAlive()){
		HandleInput();
		UpdateGame();
		DrawGame();
	}
}
// Neat little update function
void Game::UpdateGame(){
	// Simulate Everything here.
	if (inState != GameState::GAME_PAUSE){
		SDL_SetRelativeMouseMode(SDL_TRUE);
		mx = input->GetMouseX();
		my = input->GetMouseY();
		player.Update(ClockTimer::returnDeltatime(TimeMeasure::TIME_SECONDS), input, camera, bullets, walls);
	}
	else{
		SDL_SetRelativeMouseMode(SDL_FALSE);
	}
	model = glm::mat4();
	ClockTimer::Tick();
	if (inState == GameState::GAME_RUNNING){
		// Restore the state
		waterFX = false;
		factor = 1.88;
		player.SetSpeed(playerSpeed, playerSpeed);
		player.SetFire(1);
		for (int i = 0; i < bullets.size(); i++){
			if (!bullets[i].isActive()){
				bullets.erase(bullets.begin() + i);
			}
			bullets[i].Update(ClockTimer::returnDeltatime(TimeMeasure::TIME_SECONDS), walls);
		}
		for (int i = 0; i < testAi.size(); i++){
			if (!testAi[i].isAlive()){
				testAi.erase(testAi.begin() + i);
			}
			testAi[i].Update(ClockTimer::returnDeltatime(TimeMeasure::TIME_SECONDS), player,bullets, walls);
		}
		for (int i = 0; i < turrets.size(); i++){
			if (!turrets[i].isAlive()){
				turrets.erase(turrets.begin() + i);
			}
			turrets[i].Update(ClockTimer::returnDeltatime(TimeMeasure::TIME_SECONDS), player, bullets);
		}
		for (auto &t : triggers){
			if (t.GetName() == "triggerWater"){
				t.Update(ClockTimer::returnDeltatime(TimeMeasure::TIME_SECONDS),
					player,
					[&](Entity &t){
					player.SetFire(0);
					waterFX = true;
					player.SetSpeed(40, 40);
					factor = 1.10;
				},
					[&](Entity &t){
				});
			}
			for (auto & ai : testAi){
				if (t.GetName() == "triggerWater"){
					t.Update(ClockTimer::returnDeltatime(TimeMeasure::TIME_SECONDS),
						ai,
						[&](Entity &t){
							t.SetSpeed(40, 40);
					},
						[&](Entity &t){
					});
				}
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
	glClearColor(0.f, 0.0f, .0f, 1.0f);
	camera->Identity();
	camera->Translate(glm::vec2(-(-player.GetPosition().x*camera->GetScale() + width/2), -(-player.GetPosition().y*camera->GetScale() + height/2)));
	camera->SetCameraSize(glm::vec2(width * camera->GetScale(), height * camera->GetScale()-0.02));
	camera->SetCameraLocation(glm::vec2(player.GetPosition().x/camera->GetScale() - width/factor, player.GetPosition().y/camera->GetScale() - height/factor));

	camera->Scale(glm::vec2(scale.x, scale.y)); // camera system.
	view = camera->RetrieveMatrix(); // Call this to transfer matrix.
	program->SetUniformMatrix4fv("view", glm::value_ptr(view));
	if (inState == GameState::GAME_MENU){
	}
		renderer->Begin();
		renderer->BindTexture(*Textures["grass"]);
		renderer->Draw(glm::vec2(-512.0f, -512.f), glm::vec2(4096.0f), 0);
		// walls
		for (auto& wll : walls){
			// Compare the name of these things to all possible wall name values
			if (camera->InBounds(wll.GetPosition(), wll.GetSize())){
				if (wll.GetName() == "water"){
					renderer->BindTexture(*Textures[wll.GetName()]);
					renderer->SetColor(wll.GetColor());
					renderer->DrawWater(wll.GetPosition(), wll.GetSize(), 0);
					renderer->PassInUniform("offset", 15.3f / ClockTimer::returnElaspedTime(TimeMeasure::TIME_SECONDS));
				}
				else if (wll.GetName() == "wall-dev" || wll.GetName() == "dev" || wll.GetName() == "wood-floor" || wll.GetName() == "smooth-stone" || wll.GetName() == "warning"){
					renderer->BindTexture(*Textures[wll.GetName()]);
					renderer->SetColor(wll.GetColor());
					renderer->Draw(wll.GetPosition(), wll.GetSize(), 0);
				}
				else{
					renderer->SetColor(wll.GetColor());
					renderer->DrawRect(wll.GetPosition(), wll.GetSize(), 0);
				}
			}
		}
		renderer->BindTexture(*Textures["player"]);
		for (auto & ai : testAi){
			renderer->SetColor(ai.GetColor());
			if (camera->InBounds(ai.GetPosition(), ai.GetSize())){
				renderer->Draw(ai.GetPosition(), ai.GetSize(), ai.GetAngle());
			}
		}
		renderer->SetColor(player.GetColor());
		renderer->Draw(player.GetPosition(), player.GetSize(), player.GetAngle());
		renderer->BindTexture(*Textures["turret"]);
		for (auto & ai : turrets){
			renderer->SetColor(ai.GetColor());
			if (camera->InBounds(ai.GetPosition(), ai.GetSize())){
				renderer->Draw(ai.GetPosition(), ai.GetSize(), ai.GetAngle());
			}
		}
		//Everything else
		renderer->BindTexture(*Textures["bullet"]);
		for (auto & proj : bullets){
			if (camera->InBounds(proj.GetPosition(), proj.GetSize()))
			renderer->Draw(proj.GetPosition(), proj.GetSize(), proj.GetAngle());
		}
		renderer->End();
	FrameBuffer->End();

	glClear(GL_COLOR_BUFFER_BIT);

	scrProgram->SetUniform1i("waterFX", waterFX);
	scrProgram->SetUniform1i("glitch", glitch);
	scrProgram->SetUniform1i("greyScale", greyScale);
	scrProgram->SetUniform1f("offSet", 0.5f * ClockTimer::returnElaspedTime(TimeMeasure::TIME_SECONDS));
	scrProgram->Use();
	FrameBuffer->Render();
	scrProgram->Unuse();

	// Reset the camera so it doesn't "Move" with the game
	camera->Identity();
	view = camera->RetrieveMatrix(); // Call this to transfer matrix.
	program->SetUniformMatrix4fv("view", glm::value_ptr(view));
	renderer->Begin();
	renderer->SetColor(glm::vec3(255));
	renderer->BindTexture(*vig);
	renderer->Draw(glm::vec2(0, 0), glm::vec2(width, height), 0);
	renderer->UnbindTexture(*vig);
	renderer->SetColor(glm::vec3(0));
	renderer->DrawRect(glm::vec2(0, 15), glm::vec2(300, 50), 0);
	renderer->SetColor(glm::vec3(255, 0 ,0));
	renderer->DrawRect(glm::vec2(40/2, (10+20)/2), glm::vec2(20/2, 80/2), 0);
	renderer->DrawRect(glm::vec2(10/2, (40+20)/2), glm::vec2(80/2, 20/2), 0);
	renderer->SetColor(glm::vec3(100, 233, 75));
	renderer->DrawRect(glm::vec2(60, 40), glm::vec2(player.GetHealth()*2, 20), 0);
	renderer->BindTexture(*Textures["player"]);
	renderer->SetColor(glm::vec3(255));
	renderer->Draw(glm::vec2(20, 70), glm::vec2(50), player.GetAngle());
	renderer->End();

	smArial->Render("Health Bar", glm::vec2(60, 20), 1, glm::vec3(255));
	if (inState == GameState::GAME_PAUSE || inState == GameState::GAME_MENU){
		greyScale = true;
		renderer->Begin();
		renderer->DrawRect(glm::vec2(width / 2 - 150, height / 2-32), glm::vec2(370, 90), 0);
		arial->Render("Game Paused", glm::vec2(width / 2 - 150, height / 2), 1, glm::vec3(0));
		renderer->End();
	}
	else{
		greyScale = false;
	}
	window->Refresh();
}

void Game::HandleInput(){
	input->Update();
	input->PollEvents([&](SDL_Event* evnt){
		switch (evnt->type){
		case SDL_QUIT:
			inState = GameState::GAME_QUIT;
			window->ShouldClose(true);
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
	input->isKeyPressed(SDL_SCANCODE_SPACE, [&](){
		player.FireBullet(bullets);
	});
	player.SetAngle(atan2(input->GetMouseY() - player.GetPosition().y, input->GetMouseX() - player.GetPosition().x));
}
