#pragma once
#include <GL\glew.h>
#include <string>
class Shader
{
public:
	Shader(GLenum sh);
	void LoadFromFile(std::string path);
	void LoadFromSource(char* code);
	GLuint GetObject() { return shaderObject; }
	~Shader();
private:
	GLuint shaderObject;
};

