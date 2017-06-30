#pragma once
#include "dllDef.h"
#include <GL\glew.h>
// Forward Declaration
class Shader;
/*	
	ShaderProgram

	OpenGL ShaderProgram wrapper.
	Again most of the wrapper ensures that you do the least amount of work.

	It also contains helper utilities for commonly used uniform value setter functions
	Very easy to use
*/
class ShaderProgram
{
public:
	OATS_LIB_API ShaderProgram();
	OATS_LIB_API ~ShaderProgram();
	OATS_LIB_API GLuint GetObject();
	OATS_LIB_API void AddShader(Shader& sh);
	OATS_LIB_API void DetachShader(Shader& sh);
	OATS_LIB_API void LinkProgram();
	OATS_LIB_API void Use();
	OATS_LIB_API void Unuse();
	OATS_LIB_API bool isInUse() const;
	// Uniform Functions
	// TODO: Use Specialized Templates for all of this.
	OATS_LIB_API void SetUniform1i(const char* location, int v0);
	OATS_LIB_API void SetUniform1f(const char* location, float v0);
	OATS_LIB_API void SetUniform2f(const char* location, float v0, float v1);
	OATS_LIB_API void SetUniform3f(const char* location, float v0, float v1, float v2);
	OATS_LIB_API void SetUniform4f(const char* location, float v0, float v1, float v2, float v3);

	OATS_LIB_API void SetUniform4fv(const char* location, float* value);
	OATS_LIB_API void SetUniformMatrix4fv(const char* location, float* value);
private:
	bool use;
	GLuint sObject;
};

