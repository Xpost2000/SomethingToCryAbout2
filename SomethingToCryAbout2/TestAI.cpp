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

void TestAI::Update(float dt){
	if (aiCoolDown < 0 || aiCoolDown == 0){
		aiCoolDown = 90;
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> distr(0, 360);
		std::uniform_int_distribution<> decide(1, 4);
		angle = distr(gen);
		decidingMove = decide(gen);
		std::cout << decidingMove << std::endl;
	}
	if (aiCoolDown != 0 || aiCoolDown > 0){
		MoveFromAngle(dt, decidingMove);
		aiCoolDown--;
	}
}