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
	const GLuint GetVao() const { return vao; }
	OATS_LIB_API bool isBound() const;
	OATS_LIB_API void Bind();
	OATS_LIB_API void Unbind();
	OATS_LIB_API void Attrib(const GLint index, const GLint size, const GLboolean normalized, const int stride, const int offset);
	OATS_LIB_API void Draw(const GLenum type, const GLint count);
	// More explicit drawing. Requires manual binding
	OATS_LIB_API static void DrawArrays(const GLenum type, const GLint count);
private:
	bool bound;
	GLuint vao;
};

