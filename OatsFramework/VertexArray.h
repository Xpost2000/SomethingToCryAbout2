#pragma once
#include <GL/glew.h>
#include "dllDef.h"
class VertexArray
{
public:
	OATS_LIB_API VertexArray();
	OATS_LIB_API ~VertexArray();
	OATS_LIB_API void Bind();
	OATS_LIB_API static void Unbind();
	OATS_LIB_API void Attrib(GLint index, GLint size, GLboolean normalized, int stride, int offset);
	OATS_LIB_API void Draw(GLenum type, GLint count);
private:
	GLuint vao;
};

