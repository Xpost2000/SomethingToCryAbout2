#include "Trigger.h"


Trigger::Trigger() :Entity(glm::vec2(0), glm::vec2(2), glm::vec3(0), 0, "trigger", false)
{
}


Trigger::~Trigger()
{
}

void Trigger::Update(float dt, Entity &other, std::function<void()> action, std::function<void()> opposite){
	if (AABBCollide(other)){
		action();
	}
	else{
		opposite();
	}
}
