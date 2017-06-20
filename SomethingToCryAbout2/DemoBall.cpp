#include "DemoBall.h"


DemoBall::DemoBall(glm::vec2 pos, glm::vec2 size, glm::vec3 color)
{
	r = color.r; g = color.g; b = color.b;
	w = size.x; h = size.y;
	x = pos.x; y = pos.y;
}


DemoBall::~DemoBall()
{
}

void DemoBall::CollideWithBounds(float dt){
	if (y+h > bnds.u || y < bnds.d){
		vY = -vY;
		x += 120 * dt;
	}
	else{
		return;
	}
}

void DemoBall::Update(float dt){
	y += vY;

	CollideWithBounds(dt);
}

void DemoBall::SetBounds(int l, int r, int u, int d){
	bnds.l = l;
	bnds.r = r;
	bnds.u = u;
	bnds.d = d;
}