/*
	Define minor helper functions for mathematics

	Also includes all GLM headers.
*/

#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <glm\glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
// (floating value) Turn Radian values into Degrees.
inline float toDegrees(float radians){
	return(float)(radians * (180.0f/M_PI));
}
// (floating value) Turn Degree values into Radians
inline float toRadians(float degrees){
	return(float)(degrees * (M_PI/180.0f));
}

#undef _USE_MATH_DEFINES