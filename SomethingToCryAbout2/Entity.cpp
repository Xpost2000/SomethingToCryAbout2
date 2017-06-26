#include "Entity.h"

Entity::Entity(glm::vec2 pos, glm::vec2 size, glm::vec3 color, int health, std::string name, bool collidable){
	position = pos;
	this->size = size;
	this->color = color;
	this->health = health;
	this->name = name;
	bActive = true;
	bCollide = collidable;
}

Entity::Entity() : Entity(glm::vec2(0), glm::vec2(10), glm::vec3(255), 100, "Bob", true)
{
}


Entity::~Entity()
{
}

void Entity::SetPos(float x, float y){
	position = glm::vec2(x, y);
}

void Entity::SetName(std::string name){
	this->name = name;
}

void Entity::SetSize(float x, float y){
	size = glm::vec2(x, y);
}

void Entity::SetColor(float r, float g, float b){
	color = glm::vec3(r, g, b);
}

void Entity::SetHealth(int hp){
	health = hp;
}

const glm::vec2 Entity::GetPosition() const{
	return position;
}

const glm::vec3 Entity::GetColor() const{
	return color;
}

const glm::vec2 Entity::GetSize() const{
	return size;
}

const std::string Entity::GetName() const{
	return name;
}

const int Entity::GetHealth() const{
	return health;
}

bool Entity::AABBCollide(const Entity& other) const{
	/*
		Return the value of this expression
	*/
	return (position.x < other.position.x + other.size.x&&
			position.x + size.x > other.position.x) && 
			(position.y < other.position.y + other.size.y && 
			position.y + size.y > other.position.y);
}

void Entity::MoveUp(float dt){
	position.y -= vY * dt;
}

void Entity::MoveDown(float dt){
	position.y += vY * dt;
}

void Entity::MoveLeft(float dt){
	position.x -= vX * dt;
}

void Entity::MoveRight(float dt){
	position.x += vX * dt;
}

void Entity::SideCollide(const Entity &other, float dt){
	/*
		Calculate the dimensions 
	*/
	if (other.bCollide){
		float pBottom = position.y + size.y;
		float oBottom = other.position.y + other.size.y;
		float pRight = position.x + size.x;
		float oRight = other.position.x + other.size.x;

		// our bottom to their top
		float tCollide = pBottom - other.position.y;
		// their bottom to our top
		float bCollide = oBottom - position.y;
		float rCollide = oRight - position.x;
		float lCollide = pRight - other.position.x;

		if (tCollide < bCollide && tCollide < lCollide && tCollide < rCollide){
			position.y -= vY*dt;
			printf("Top\n");
		}
		if (bCollide < tCollide && bCollide < lCollide && bCollide < rCollide){
			position.y += vY*dt;
			printf("Bottom\n");
		}
		if (lCollide < rCollide && lCollide < tCollide && lCollide < bCollide){
			position.x -= vY*dt;
			printf("Left\n");
		}
		if (rCollide < lCollide && rCollide < tCollide && rCollide < bCollide){
			position.x += vY*dt;
			printf("Right\n");
		}
	}
	else{
		return;
	}
}