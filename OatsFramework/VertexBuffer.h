#pragma once
#include <GL/glew.h>
#include <vector>
#include "dllDef.h"
#include <glm\glm.hpp>
/*
	Vertex buffer Object class

	This takes care of most of the hard lifting.
	You can add vertices manually using the AddVerticies function.
	BufferData is pretty much automatically dealt with.

	Also has helper vertex count function
*/
class VertexBuffer
{
public:
	OATS_LIB_API VertexBuffer();
	OATS_LIB_API ~VertexBuffer();
	OATS_LIB_API void AddVertices(const float x, const float y);
	OATS_LIB_API void AddVertices(const float x, const float y, const float z);
	OATS_LIB_API void AddVertices3fv(const float[3]);
	OATS_LIB_API void AddVertices2fv(const float[2]);
	OATS_LIB_API void AddVerticesVec2(const glm::vec2);
	OATS_LIB_API void AddVerticesVec3(const glm::vec3);
	OATS_LIB_API void BufferData();
    const GLint GetVertexCount() const{ return vertices; }
	OATS_LIB_API void Bind();
	OATS_LIB_API static void Unbind();
private:
	GLuint vbo;
	GLint vertices;
	std::vector<float> data;
};

