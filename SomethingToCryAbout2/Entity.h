#pragma once
#include <string>
#include <glm\glm.hpp>
/*
	Basic Entity Class to be inherited from.
	These will be attributes that all entities
	share

	So the goal is to make this as broad as possible.
	Do not expose any private members if I don't have to.
*/

#define DIR_FORWARD 1
#define DIR_BACKWARD 2

class Entity
{
public:
	Entity(glm::vec2 pos, glm::vec2 size, glm::vec3 color, int health, std::string name, bool collidable);
	Entity();
	~Entity();
	virtual void Update() {}
	virtual void Update(float dt){}
	void SetSpeed(float x, float y) { vX = x; vY = y; }
	void SetHealth(int hp);
	void SetName( std::string name );
	void SetPos( float x, float y);
	void SetSize(float x, float y);
	void SetColor( float r, float g, float b );
	const glm::vec2 GetPosition() const;
	const glm::vec2 GetSize() const;
	const glm::vec3 GetColor() const;
	const std::string GetName() const;
	void MoveLeft(float dt);
	void MoveRight(float dt);
	void MoveUp(float dt);
	void MoveDown(float dt);
	const int GetHealth() const;
	bool AABBCollide(const Entity& other) const;
	void SideCollide(const Entity &other, float dt);
	bool isAlive() { bActive = (health > 0); return bActive; };
	bool isActive() { return bActive; }
	void SetActive(bool val) { bActive = val; }
	const float GetAngle() const { return angle; }
	void SetAngle(float x) { angle = x; }
	void RotateRight(float x, float dt) { angle += x *dt; }
	void RotateLeft(float x, float dt) { angle -= x *dt; }
	void SetCollidable(bool val) { bCollide = val; }
	void MoveFromAngleFront(float dt);
	void MoveFromAngleBack(float dt);
	// This is more flexible
	void MoveFromAngle(float dt, int direction);
private:
	float vX;
	float vY;
	int health;
	bool bCollide; // Collidable?
protected:
	float angle;
	bool bActive;
private:
	std::string name;
	glm::vec2 size;
	glm::vec3 color;
	glm::vec2 position;
};

