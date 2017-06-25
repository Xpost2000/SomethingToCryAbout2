#pragma once
#include <string>
#include <glm\glm.hpp>
class Button
{
public:
	Button(glm::vec2 pos, glm::vec2 size, glm::vec3 clr, glm::vec3 txClr, std::string txt);
	~Button();
	void SetID(int id) { this->id = id; }
	int GetId() { return id; }
	bool IsInBounds(int &x, int &y);
	std::string GetString() { return text; }
	glm::vec2 GetLoc() { return location; }
	glm::vec2 GetSize() { return size; }
	glm::vec3 GetColor() { return color; }
	glm::vec2 GetTextLoc() { return glm::vec2(location.x + size.x/5, location.y + size.y*.15); }
	glm::vec3 GetTextColor() { return textColor; }
private:
	int id;
	std::string text;
	glm::vec2 location;
	glm::vec2 size;
	glm::vec3 color;
	glm::vec3 textColor;
};

