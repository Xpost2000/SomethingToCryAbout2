#include "VertexBuffer.h"


VertexBuffer::VertexBuffer()
{
	glGenBuffers(1, &vbo);
	fprintf(stderr, "VertexBuffer : Created Instance\n");
}


VertexBuffer::~VertexBuffer()
{
	fprintf(stderr, "VertexBuffer : Destructor\n");
	glDeleteBuffers(1, &vbo);
}

void VertexBuffer::AddVertices(float x, float y){
	data.push_back(x); data.push_back(y);
	vertices++;
	fprintf(stderr, "VertexBuffer : Added Vertex\n");
}

void VertexBuffer::AddVertices(float x, float y, float z){
	data.push_back(x); data.push_back(y); data.push_back(z);
	vertices++;
	fprintf(stderr, "VertexBuffer : Added Vertex\n");
}

void VertexBuffer::Bind(){
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	fprintf(stderr, "VertexBuffer : Bound VBO\n");
}

void VertexBuffer::Unbind(){
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	fprintf(stderr, "VertexBuffer : Unbound VBO\n");
}

void VertexBuffer::BufferData(){
	Bind();
	glBufferData(GL_ARRAY_BUFFER, data.size() *sizeof(float), &data[0], GL_STATIC_DRAW);
	Unbind();
	fprintf(stderr, "VertexBuffer : Set Buffer Data\n");
}