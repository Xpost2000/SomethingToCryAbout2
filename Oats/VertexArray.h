#pragma once
#include <GL/glew.h>
#include "dllDef.h"
/*
	Simple Vertex Array object class.
	Does most of the work and provides simple functions that 
	still provide you with fair amounts of control over the internals.
*/
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
