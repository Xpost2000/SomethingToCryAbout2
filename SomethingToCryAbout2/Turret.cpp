#include "Turret.h"
#include <cmath>
#include "Player.h"
#include <Oats\MathHelperFunctions.h>
Turret::Turret()
{
}


Turret::~Turret()
{
}

void Turret::Update(float dt, Player& player, std::vector<Bullet> &bullets){

	if (abs(abs(player.GetPosition().x) - abs(GetPosition().x)) <= STANDARD_SIZE*8.8 && abs(abs(player.GetPosition().y) - abs(GetPosition().y) <= STANDARD_SIZE*8.8)){
		float angle = atan2(player.GetPosition().y - GetPosition().y, player.GetPosition().x - GetPosition().x);
		SetAngle(angle);
		if (firingCoolDown <= 0){
			firingCoolDown = 40;
			bullets.push_back(Bullet(glm::vec2(GetPosition()), glm::vec2(STANDARD_SIZE / 2), glm::vec3(255), 10, "Tbullet", false, 1220));
			bullets.back().SetAngle(GetAngle());
			bullets.back().SetSpeed(500, 500);
		}
	}
	for (int i = 0; i < bullets.size(); i++){
		if (bullets[i].AABBCollide(*this) && bullets[i].GetName() != "Tbullet"){
			SubtractToHealth(30);
			bullets[i].SetActive(0);
		}
	}
	if (fxCoolDown > 0){
		fxCoolDown--;
	}
	else{
		SetColor(255, 255, 255);
		fxCoolDown = 20;
	}
	firingCoolDown--;
}