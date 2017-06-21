#pragma once
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm/gtc\type_ptr.hpp>
#include "dllDef.h"
/*
	It's a neat little interface
*/
class Camera2D
{
public:
	OATS_LIB_API Camera2D(glm::mat4& matrix, float mX, float mY);
	OATS_LIB_API ~Camera2D();
	OATS_LIB_API void SupplyMatrix(glm::mat4 &matrix);
	OATS_LIB_API void Translate(glm::vec2 location);
	OATS_LIB_API void Scale(glm::vec2 amount);
	OATS_LIB_API glm::mat4 RetrieveMatrix();
private:
	float maxBoundX, maxBoundY;
	glm::mat4 viewMatrix;
};

