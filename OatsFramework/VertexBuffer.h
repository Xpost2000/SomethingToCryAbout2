#pragma once
#include <GL/glew.h>
#include <vector>
#include "dllDef.h"
class VertexBuffer
{
public:
	OATS_LIB_API VertexBuffer();
	OATS_LIB_API ~VertexBuffer();
	OATS_LIB_API void AddVertices(float x, float y);
	OATS_LIB_API void AddVertices(float x, float y, float z);
	OATS_LIB_API void BufferData();
    GLint GetVertexCount() { return vertices; }
	OATS_LIB_API void Bind();
	OATS_LIB_API void Unbind();
private:
	GLuint vbo;
	GLint vertices;
	std::vector<float> data;
};

