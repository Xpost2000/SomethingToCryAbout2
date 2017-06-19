#pragma once
#include <glm\glm.hpp>
/*
This is to test if this renderer rendering
supplied information is a good approach
*/
class DemoBall
{
public:
	DemoBall(glm::vec2 pos, glm::vec2 size, glm::vec3 color);
	~DemoBall();
	void SetVelocity(const float speed) { vY = speed; }
	void SetBounds(int l, int r, int u, int d);
	void Update(float dt);
	glm::vec2 GetPos() { return glm::vec2(x, y); }
	glm::vec2 GetSize() { return glm::vec2(w, h); }
	glm::vec3 GetColor() { return glm::vec3(r, g, b); }
	void CollideWithBounds(float dt);
	struct ScrBounds{
		int l;
		int r;
		int u;
		int d;
	}bnds;
	float vY;
	float x, y;
	float w, h;
	float r, g, b;
};

