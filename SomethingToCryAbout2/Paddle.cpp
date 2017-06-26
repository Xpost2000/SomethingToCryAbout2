#include "Paddle.h"
#include <cmath>

Paddle::Paddle(glm::vec2 position, glm::vec2 size)
{
	pos = position;
	this->size = size;
}


Paddle::~Paddle()
{
}

void Paddle::MoveUp(float dt){
	if (pos.y < 0){
		return;
	}
	pos.y -= 270.0f * dt;
}

void Paddle::MoveDown(float dt){
	if (pos.y + size.y > 768){
		return;
	}
	pos.y += 270.0f * dt;
}

bool Paddle::Collide(Ball &ball){
	if ((pos.x < ball.GetPos().x + ball.GetSize().x &&
		ball.GetPos().x < pos.x + size.x)
		&& (pos.y < ball.GetPos().y + ball.GetSize().y &&
			ball.GetPos().y < pos.y + size.y)){
		return true;
	}
	else{
		return false;
	}
}