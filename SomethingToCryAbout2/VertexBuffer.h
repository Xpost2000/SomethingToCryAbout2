#pragma once
#include <GL/glew.h>
#include <vector>
class VertexBuffer
{
public:
	VertexBuffer();
	~VertexBuffer();
	void AddVertices(float x, float y);
	void AddVertices(float x, float y, float z);
	void BufferData();
	GLint GetVertexCount() { return vertices; }
	void Bind();
	void Unbind();
private:
	GLuint vbo;
	GLint vertices;
	std::vector<float> data;
};

