#pragma once
#include <Oats\Camera2D.h>
#include <Oats\InputManager.h>
#include "Entity.h"

/*
	Since pretty much 100% of the work is done inside of the entity class
	The player isn't super important to build on

	This class is just going to manage the Game related Input handling for a player.
	*/

class Player : public Entity
{
public:
	// Just let the entity implementation take care of this
	Player(glm::vec2 pos, glm::vec2 size, glm::vec3 color, int health, std::string name, bool collidable)
	: Entity(pos, size, color, health, name, collidable){
	}
	Player();
	~Player();
	void Update() {}
	void Update(float dt) {} // This is so I techincally "implement the virtual update func"
	void Update(float dt, InputManager *man, Camera2D* camera); // Add my own input function
private:
};

