#pragma once
#define MAX_PROJECTILES 200
/*
Simple yet fun class
*/
#include "Entity.h"
class Bullet : public Entity
{
public:
	Bullet(glm::vec2 pos, glm::vec2 size, glm::vec3 color, int health, std::string name, bool collidable, int lifeTime)
		: Entity(pos, size, color, health, name, collidable){
		LifeTime = lifeTime;
	}
	Bullet();
	~Bullet();
	void Update() {}
	void Update(float dt, std::vector<Entity> &others);
private:
	int LifeTime;
};

