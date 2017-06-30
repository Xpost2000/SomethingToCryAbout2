#include "Player.h"
#include <Oats\MathHelperFunctions.h>
Player::Player() : Entity(glm::vec2(300), glm::vec2(10), glm::vec3(255), 100, "Bob", true)
{
}


Player::~Player()
{
}

void Player::Update(float dt, InputManager *input, Camera2D*camera){
	/*
	Use lambda's to fix all of this
	*/
	input->isKeyPressed(SDL_SCANCODE_Z, [&](){
		camera->IncreaseScale(2 * dt);
	});
	input->isKeyPressed(SDL_SCANCODE_X, [&](){
		camera->DecreaseScale(2 * dt);
	});
	input->isKeyPressed(SDL_SCANCODE_W, [&](){
		MoveUp(dt);
	});
	input->isKeyPressed(SDL_SCANCODE_S, [&](){
		MoveDown(dt);
	});
	input->isKeyPressed(SDL_SCANCODE_A, [&](){
		MoveLeft(dt);
	});
	input->isKeyPressed(SDL_SCANCODE_D, [&](){
		MoveRight(dt);
	});
	input->isKeyPressed(SDL_SCANCODE_LEFT, [&](){
		RotateLeft(10, dt);
	});
	input->isKeyPressed(SDL_SCANCODE_RIGHT, [&](){
		RotateRight(10, dt);
	});
}