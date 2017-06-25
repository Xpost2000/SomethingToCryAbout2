#pragma once
#include <GL\glew.h>
#include <string>
#include "dllDef.h"
/*
	Shader 
	OpenGL Shader class wrapper.
	It takes care of virtually everything but incase you ever actually want to make
	4 function calls on your own you may access the handle directly.
*/
class Shader
{
public:
	OATS_LIB_API Shader(GLenum sh);
	OATS_LIB_API void LoadFromFile(std::string path);
	OATS_LIB_API void LoadFromSource(char* code);
	GLuint GetObject() { return shaderObject; }
	OATS_LIB_API ~Shader();
private:
	GLuint shaderObject;
};

