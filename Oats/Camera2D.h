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
	OATS_LIB_API Camera2D(glm::mat4& matrix, float mX, float mY);
	OATS_LIB_API ~Camera2D();
	// Give the camera the reference of a matrix
	OATS_LIB_API void SupplyMatrix(glm::mat4 &matrix);
	// Translate the camera to another location
	OATS_LIB_API void Translate(glm::vec2 location);
	// Scale the camera matrix ( zoom in or out )
	OATS_LIB_API void Scale(glm::vec2 amount);
	void Identity(){
		viewMatrix = glm::mat4();
	}
	// Retrieve the value of the matrix of this camera
	OATS_LIB_API glm::mat4 RetrieveMatrix();
private:
	float maxBoundX, maxBoundY;
	glm::mat4 viewMatrix;
};

