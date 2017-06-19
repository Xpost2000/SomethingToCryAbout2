#pragma once
#include <GL\glew.h>
class Shader;
class ShaderProgram
{
public:
	ShaderProgram();
	~ShaderProgram();
	GLuint GetObject();
	void AddShader(Shader& sh);
	void DetachShader(Shader& sh);
	void LinkProgram();
	void Use();

	// Uniform Functions
	// TODO: Use Specialized Templates for all of this.
	void SetUniform1i(const char* location, int v0);
	void SetUniform1f(const char* location, float v0);
	void SetUniform2f(const char* location, float v0, float v1);
	void SetUniform3f(const char* location, float v0, float v1, float v2);
	void SetUniform4f(const char* location, float v0, float v1, float v2, float v3);

	void SetUniform4fv(const char* location, float* value);
	void SetUniformMatrix4fv(const char* location ,float* value);
private:
	GLuint sObject;
};

