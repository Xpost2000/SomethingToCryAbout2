#include "VertexBuffer.h"


VertexBuffer::VertexBuffer()
{
	glGenBuffers(1, &vbo);
}


VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &vbo);
}

void VertexBuffer::AddVertices(float x, float y){
	data.push_back(x); data.push_back(y);
}

void VertexBuffer::AddVertices(float x, float y, float z){
	data.push_back(x); data.push_back(y); data.push_back(z);
}

void VertexBuffer::Bind(){
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
}

void VertexBuffer::Unbind(){
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
}

void VertexBuffer::BufferData(){
	Bind();
	glBufferData(GL_ARRAY_BUFFER, data.size() *sizeof(float), &data[0], GL_STATIC_DRAW);
	Unbind();
}