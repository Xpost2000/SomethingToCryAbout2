#pragma once
#include "Entity.h"
class TestAI : public Entity
{
public:
	TestAI(glm::vec2 pos, glm::vec2 size, glm::vec3 color, int health, std::string name, bool collidable)
		: Entity(pos, size, color, health, name, collidable){
	}
	TestAI();
	~TestAI();

	void Update();
	void Update(float dt);
private:
	int decidingMove;
	float targAngle;
	int aiCoolDown = 0;
};

