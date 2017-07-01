#include "TestAI.h"
#include <random>
#include <iostream>
TestAI::TestAI()
{
}


TestAI::~TestAI()
{
}

void TestAI::Update(){

}

void TestAI::Update(float dt, std::vector<Bullet>& bullets, std::vector<Entity> &others){
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
		MoveFromAngle(dt, decidingMove);
		aiCoolDown--;
		if (fxCoolDown > 0){
			fxCoolDown--;
		}
		else{
			SetColor(255, 255, 255);
		}
	}
	for (int i = 0; i < bullets.size(); i++){
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
}