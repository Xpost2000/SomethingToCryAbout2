#include "Trigger.h"


Trigger::Trigger() :Entity(glm::vec2(0), glm::vec2(2), glm::vec3(0), 0, "trigger", false)
{
}


Trigger::~Trigger()
{
}

void Trigger::Update(float dt, Entity& other, std::function<void(Entity&)> action, std::function<void(Entity&)> opposite){
	if (AABBCollide(other)){
		action(other);
	}
	else{
		opposite(other);
	}
}