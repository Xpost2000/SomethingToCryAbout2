#include "Camera2D.h"


Camera2D::Camera2D(glm::mat4& matrix, float mX, float mY, float sX, float sY) :
viewMatrix(matrix), maxBoundX(mX), maxBoundY(mY), maxScaleX(sX), maxScaleY(sY)
{
	viewMatrix = glm::ortho(0.f, maxBoundX, 0.f, maxBoundY);
}


Camera2D::~Camera2D()
{
}

void Camera2D::SupplyMatrix(glm::mat4& matrix){
	viewMatrix = matrix;
}

void Camera2D::Translate(glm::vec2 location){
	viewMatrix = glm::translate(viewMatrix, glm::vec3(location.x, location.y, 0.0));
}

void Camera2D::Scale(glm::vec2 amount){
	viewMatrix = glm::scale(viewMatrix, glm::vec3(amount.x*scale / maxBoundX, amount.y*scale / maxBoundY, 1.0));
}

glm::mat4 Camera2D::RetrieveMatrix(){
	return viewMatrix;
}

void Camera2D::SetBounds(float x, float y){
	maxBoundX = x;
	maxBoundY = y;
}

void Camera2D::SetScale(float x){
	scale = x;
}

void Camera2D::IncreaseScale(float amnt){
	if (scale < maxScaleX)
	scale += amnt;
}

void Camera2D::DecreaseScale(float amnt){
	if (scale > maxScaleY)
	scale -= amnt;
}

void Camera2D::SetScaleBounds(float x, float y){
	maxScaleX = x;
	maxScaleY = y;
}