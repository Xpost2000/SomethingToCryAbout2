/*
	Define minor helper functions for mathematics

	Also includes all GLM headers.
*/

#pragma once
#include <glm\glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SDL2\SDL_stdinc.h>
// (floating value) Turn Radian values into Degrees.
inline float toDegrees(float radians){
	return(float)(radians * (180.0f/M_PI));
}
// (floating value) Turn Degree values into Radians
inline float toRadians(float degrees){
	return(float)(degrees * (M_PI/180.0f));
}