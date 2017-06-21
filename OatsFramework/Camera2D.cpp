#include "Camera2D.h"


Camera2D::Camera2D(glm::mat4& matrix, float mX, float mY) :
viewMatrix(matrix), maxBoundX(mX), maxBoundY(mY)
{
}


Camera2D::~Camera2D()
{
}

void Camera2D::SupplyMatrix(glm::mat4& matrix){
	viewMatrix = matrix;
}

void Camera2D::Translate(glm::vec2 location){
	viewMatrix = glm::translate(viewMatrix, glm::vec3(location, 1.0));
}

void Camera2D::Scale(glm::vec2 amount){
	viewMatrix = glm::scale(viewMatrix, glm::vec3(amount.x / maxBoundX, amount.y / maxBoundY, 1.0));
}

glm::mat4 Camera2D::RetrieveMatrix(){
	return viewMatrix;
}