#include "Button.h"


Button::Button(glm::vec2 pos, glm::vec2 size, glm::vec3 clr, glm::vec3 txClr, std::string txt)
{
	location = pos;
	this->size = size;
	color = clr;
	textColor = txClr;
	text = txt;
}


Button::~Button()
{
}

bool Button::IsInBounds(int &x, int &y){
	bool inside = true;
	if (x > location.x + size.x){
		printf("Mouse is Outside\n");
		inside = false;
	}
	else if (x < location.x){
		printf("Mouse is Outside\n");
		inside = false;
	}
	if (y > location.y + size.y){
		printf("Mouse is Outside\n");
		inside = false;
	}
	else if (y < location.y){
		printf("Mouse is Outside\n");
		inside = false;
	}
	if (inside){
		printf("Mouse is Inside\n");
	}
	return inside;
}