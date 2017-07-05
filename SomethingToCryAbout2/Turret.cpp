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
	}
}