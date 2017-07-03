#pragma once
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm/gtc\type_ptr.hpp>
#include "dllDef.h"
/*
	Camera2D Class

	it's a simple interface and should probably be a struct.
	It holds a view matrix that it will retrieve from an application.
	Then once it modifies it's own matrix it will return that matrix to another matrix.

	There is no rotation for this camera because I did not feel the need that it would be required
	You may make an inherited camera that supports rotation
*/
class Camera2D
{
public:
	// Constructor. Provide a single matrix, and the boundaries of the camera
	OATS_LIB_API Camera2D(glm::mat4& matrix, float mX, float mY , float sX, float sY);
	OATS_LIB_API ~Camera2D();
	OATS_LIB_API void SetBounds(float x, float y);
	// Give the camera the reference of a matrix
	OATS_LIB_API void SupplyMatrix(glm::mat4 &matrix);
	// Translate the camera to another location
	OATS_LIB_API void Translate(glm::vec2 location);
	// This is setting the AABB collision box. Sorry for confusing names
	OATS_LIB_API void SetCameraLocation(glm::vec2 location);
	// This is setting the AABB collision box. Sorry for confusing names
	OATS_LIB_API void SetCameraSize(glm::vec2 size);
	// Scale the camera matrix ( zoom in or out )
	OATS_LIB_API void Scale(glm::vec2 amount);
	glm::vec2 GetPosition() { return pos; }
	glm::vec2 GetSize() { return size; }
	void Identity(){
		viewMatrix = glm::mat4();
	}
	bool InBounds(glm::vec2 pos, glm::vec2 size){
		/*
		return (position.x < other.position.x + other.size.x&&
		position.x + size.x > other.position.x) &&
		(position.y < other.position.y + other.size.y &&
		position.y + size.y > other.position.y);
		*/
		return (this->pos.x < pos.x + size.x && this->pos.x + this->size.x > pos.x) &&
				(this->pos.y < pos.y + size.y && this->pos.y + this->size.y > pos.y);
	}
	OATS_LIB_API void SetScaleBounds(float max, float min);
	OATS_LIB_API void SetScale(float x);
	OATS_LIB_API void DecreaseScale(float amnt);
	OATS_LIB_API void IncreaseScale(float amnt);
	const float GetScale() const { return scale; }
	// Retrieve the value of the matrix of this camera
	OATS_LIB_API glm::mat4 RetrieveMatrix();
private:
	float maxBoundX, maxBoundY;
	float maxScaleX, maxScaleY;
	float scale; // Uniform Scale;
	glm::vec2 pos;
	glm::vec2 size;
	glm::mat4 viewMatrix;
};

