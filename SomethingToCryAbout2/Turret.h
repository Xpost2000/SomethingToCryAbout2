#pragma once
#include "Entity.h"
class Player;
class Bullet;
class Turret : public Entity
{
public:
	Turret(glm::vec2 pos, glm::vec2 size, glm::vec3 color, int health, std::string name, bool collidable)
		: Entity(pos, size, color, health, name, collidable){
	}
	Turret();
	~Turret();
	void Update(float dt, Player& player, std::vector<Bullet>& bullets);
private:
	int firingCoolDown = 0;
};

