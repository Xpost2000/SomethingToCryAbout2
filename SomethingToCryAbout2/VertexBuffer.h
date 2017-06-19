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
	void Bind();
	void Unbind();
private:
	GLuint vbo;
	std::vector<float> data;
};

