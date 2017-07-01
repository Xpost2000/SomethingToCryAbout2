#pragma once
#include <functional>
#include "Entity.h"
class Trigger : public Entity
{
public:
	Trigger(glm::vec2 pos, glm::vec2 size, glm::vec3 color, int health, std::string name, bool collidable):
	Entity(pos, size, color, health, name, false){

	}
	// perform action on collision
	void Update(float dt, Entity &other, std::function<void()> action, std::function<void()> opposite);
	Trigger();
	~Trigger();
private:
};

