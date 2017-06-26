#pragma once
#include <glm\glm.hpp>

class Ball{
public:
	Ball(glm::vec2 position, glm::vec2 size, float vX, float vY){
		pos = position;
		this->size = size;
		this->vX = vX;
		this->vY = vY;
	}
	void Update(float dt){
		if (pos.y+size.y > 768 || pos.y < 0){
			vY = -vY;
		}
		if (pos.x+size.x > 1024 || pos.x < 0){
			vX = -vX;
		}
		pos.x += vX * dt;
		pos.y += vY * dt;
	}
	glm::vec2 GetPos() { return pos; }
	glm::vec2 GetSize() { return size; }
	void InvertVX() { vX = -vX; }
	void InvertVY() { vY = -vY; }
	glm::vec2 pos;
	glm::vec2 size;
	float vX;
	float vY;
private:
};

class Paddle
{
public:
	Paddle(glm::vec2 position, glm::vec2 size);
	~Paddle();
	bool Collide(Ball &ball);
	void MoveUp(float dt);
	void MoveDown(float dt);
	glm::vec2 GetSize() { return size; }
	glm::vec2 GetPos() { return pos; }
private:
	glm::vec2 pos;
	glm::vec2 size;
};

