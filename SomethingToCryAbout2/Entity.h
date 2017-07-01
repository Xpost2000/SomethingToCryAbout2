#pragma once
#include <vector>
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

class Player;
class Bullet;

class Entity
{
public:
	Entity(glm::vec2 pos, glm::vec2 size, glm::vec3 color, int health, std::string name, bool collidable);
	Entity();
	~Entity();
	virtual void Update() {}
	virtual void Update(float dt){}
	// Have several more overloads
	// For every possible type of implementation :(
	virtual void Update(float dt,  std::vector<Entity> &other){}
	virtual void Update(float dt, std::vector<Bullet>& bullets){}
	virtual void Update(float dt, Player &player){}
	virtual void Update(float dt, Player& player, std::vector<Bullet>& bullets){}
	virtual void Update(float dt, Player& player, std::vector<Bullet>& bullets, std::vector<Entity> &others){}
	virtual void Update(float dt, Player & player, std::vector<Entity> &others) {}
	virtual void Update(float dt, std::vector<Bullet>& bullets, std::vector<Entity> &others){}
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
	void AddToHealth(float va) { health += va; color = glm::vec3(0., 255, 155); }
	void SubtractToHealth(float va) {
		health -= va; if (fxCoolDown == 0) { color = glm::vec3(255, 15.5, 0.5); fxCoolDown = 5; }
}
	void SetHealth(float va) { health = va; }
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
	float fxCoolDown = 0;
	bool bActive;
private:
	std::string name;
	glm::vec2 size;
	glm::vec3 color;
	glm::vec2 position;
};

