#pragma once
#include <GL\glew.h>
#include <string>
#include "dllDef.h"
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

