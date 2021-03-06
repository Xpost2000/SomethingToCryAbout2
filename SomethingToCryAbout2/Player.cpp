#include "Player.h"
#include <Oats\MathHelperFunctions.h>


Player::Player() : Entity(glm::vec2(300), glm::vec2(10), glm::vec3(255), 100, "Bob", true)
{
}


Player::~Player()
{
}

void Player::FireBullet(std::vector<Bullet> &bullets){
	if (bullets.size() != MAX_PROJECTILES){
		if (bCanFire)
		if (firingCoolDown < 0){
			bullets.push_back(Bullet(glm::vec2(GetPosition()), glm::vec2(STANDARD_SIZE/2), glm::vec3(255), 10, "bullet", false, 1220));
			bullets.back().SetAngle(GetAngle());
			bullets.back().SetSpeed(550, 550);
			firingCoolDown = 20;
		}
	}
}

void Player::Update(float dt, InputManager *input, Camera2D*camera, std::vector<Bullet> &bullets, std::vector<Entity> &others){
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
	if( input->isMouseButtonPressed(MouseButton::LEFT_CLICK)){
		FireBullet(bullets);
	}
	if (input->isMouseButtonPressed(MouseButton::RIGHT_CLICK)){
	}
	firingCoolDown--;
	if (fxCoolDown > 0){
		fxCoolDown--;
	}
	else{
		SetColor(255, 255, 255);
	}
	for (size_t i = 0; i < bullets.size(); ++i){
		if (bullets[i].AABBCollide(*this) && bullets[i].GetName() != "bullet"){
			SubtractToHealth(30);
			bullets[i].SetActive(0);
		}
	}
	Update(dt, others);
}

void Player::Update(float dt, std::vector<Entity>&others){
	for (size_t i = 0; i < others.size(); ++i){
		if (AABBCollide(others[i])){
			SideCollide(others[i], dt);
		}
	}
}