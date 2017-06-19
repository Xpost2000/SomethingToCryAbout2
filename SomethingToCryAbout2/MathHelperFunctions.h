#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <glm\glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
inline float toDegrees(float radians){
	return(float)(radians * (180.0f/M_PI));
}

inline float toRadians(float degrees){
	return(float)(degrees * (M_PI/180.0f));
}

#undef _USE_MATH_DEFINES