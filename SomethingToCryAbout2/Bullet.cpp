#include "Bullet.h"


Bullet::Bullet() : Entity(glm::vec2(300), glm::vec2(10), glm::vec3(255), 100, "Bullet Bill", true)
{
	LifeTime = 250;
}


Bullet::~Bullet()
{
}

void Bullet::Update(float dt, std::vector<Entity> &others){
	if (LifeTime > 0){
		MoveFromAngle(dt, DIR_FORWARD);
		LifeTime--;
	}
	else{
		bActive = false;
	}
	for (int i = 0; i < others.size(); i++){
		if (AABBCollide(others[i]) && others[i].isCollidable()){
			printf("Entity %s : Collidable? %d\n", others[i].GetName().c_str(), others[i].isCollidable());
			SetActive(false);
		}
	}
}