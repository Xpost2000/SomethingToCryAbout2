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

	if (abs(player.GetPosition().x) - abs(GetPosition().x) <= STANDARD_SIZE*4 && abs(player.GetPosition().y) - abs(GetPosition().y) <= STANDARD_SIZE*4){
		float angle = atan2(player.GetPosition().y - GetPosition().y, player.GetPosition().x - GetPosition().x);
		SetAngle(angle);
		printf("Sentry :: Target In Sight!\n");
		if (firingCoolDown <= 0){
			firingCoolDown = 40;
			bullets.push_back(Bullet(glm::vec2(GetPosition()), glm::vec2(STANDARD_SIZE / 2), glm::vec3(255), 10, "Tbullet", false, 1220));
			bullets.back().SetAngle(GetAngle());
			bullets.back().SetSpeed(500, 500);
		}
		firingCoolDown--;
	}
}