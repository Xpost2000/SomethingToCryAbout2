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

void VertexBuffer::AddVertices(const float x, const float y){
	data.push_back(x); data.push_back(y);
	vertices++;
	fprintf(stderr, "VertexBuffer : Added Vertex\n");
}

void VertexBuffer::AddVertices(const float x, const float y, const float z){
	data.push_back(x); data.push_back(y); data.push_back(z);
	vertices++;
	fprintf(stderr, "VertexBuffer : Added Vertex\n");
}

void VertexBuffer::AddVertices3fv(const float val[3]){
	data.push_back(val[0]);
	data.push_back(val[1]);
	data.push_back(val[2]);
	vertices++;
}

void VertexBuffer::AddVertices2fv(const float val[2]){
	data.push_back(val[0]);
	data.push_back(val[1]);
	vertices++;;
}

void VertexBuffer::AddVerticesVec2(const glm::vec2 val){
	AddVertices2fv(&val[0]);
}

void VertexBuffer::AddVerticesVec3(const glm::vec3 val){
	AddVertices3fv(&val[0]);
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