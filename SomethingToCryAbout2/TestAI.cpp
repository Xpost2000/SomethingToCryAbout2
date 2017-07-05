#include "TestAI.h"
#include "Player.h"
#include <random>
#include <iostream>

/*
	I'm going to eventually modify this and turn it into the Enemy class.
	:)
*/

TestAI::TestAI()
{
}


TestAI::~TestAI()
{
}

void TestAI::Update(){

}

void TestAI::Update(float dt, Player &player, std::vector<Bullet>& bullets, std::vector<Entity> &others){
	if (aiCoolDown < 0 || aiCoolDown == 0){
		aiCoolDown = 90;
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> distr(0, 360);
		std::uniform_int_distribution<> decide(1, 4);
		angle = distr(gen);
		decidingMove = decide(gen);
	}
	if (aiCoolDown != 0 || aiCoolDown > 0){
		if (abs(abs(player.GetPosition().x) - abs(GetPosition().x))<= STANDARD_SIZE*5.8 && abs(abs(player.GetPosition().y) - abs(GetPosition().y) <= STANDARD_SIZE*5.8)){
			std::cout << " I see you" << std::endl;
			float angle = atan2(player.GetPosition().y - GetPosition().y, player.GetPosition().x - GetPosition().x);
			SetAngle(angle);

			if (firingCoolDown <= 0){
				firingCoolDown = 22;
				bullets.push_back(Bullet(glm::vec2(GetPosition()), glm::vec2(STANDARD_SIZE / 2), glm::vec3(255), 10, "Tbullet", false, 1220));
				bullets.back().SetAngle(GetAngle());
				bullets.back().SetSpeed(500, 500);
			}
			switch (decidingMove){
			case 1:
				MoveRight(dt);
				break;
			case 2:
				MoveLeft(dt);
				break;
			case 3:
				MoveUp(dt);
				break;
			case 4:
				MoveDown(dt);
				break;
			default:
				break;
			}
		}
		else{
			std::cout << "Where the f**k are you?" << std::endl;
			MoveFromAngle(dt, decidingMove);
		}
		aiCoolDown--;
		if (fxCoolDown > 0){
			fxCoolDown--;
		}
		else{
			SetColor(255, 255, 255);
		}
	}
	for (int i = 0; i < bullets.size(); i++){
		if (bullets[i].GetName() != "Tbullet")
		if (bullets[i].AABBCollide(*this)){
			SubtractToHealth(30);
			bullets[i].SetActive(0);
		}
	}
	for (int i = 0; i < others.size(); i++){
		if (AABBCollide(others[i])){
			SideCollide(others[i], dt);
		}
	}
	if (AABBCollide(player)){
		player.SideCollide(*this, dt);
		SideCollide(player, dt);
	}
	firingCoolDown--;
}