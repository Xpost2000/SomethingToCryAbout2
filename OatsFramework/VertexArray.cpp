#include "VertexArray.h"
#include <cstdio>

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &vao);
	fprintf(stderr, "VertexArray : Created Instance\n");
}


VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &vao);
	fprintf(stderr, "VertexArray : Destructor\n");
}

void VertexArray::Bind(){
	bound = true;
	glBindVertexArray(vao);
}

void VertexArray::Unbind(){
	bound = false;
	glBindVertexArray(0);
}

void VertexArray::Attrib(const GLint index, const GLint size, const GLboolean normalized, const int stride, const int offset){
	Bind();
	glVertexAttribPointer(index, size, GL_FLOAT, normalized, sizeof(float)*stride, (void*)(sizeof(float)*offset));
	glEnableVertexAttribArray(index);
	Unbind();
	fprintf(stderr, "VertexArray : Vertex Attribute Set\n");
}

void VertexArray::Draw(const GLenum type, const GLint count){
	Bind();
	glDrawArrays(type, 0, count);
	Unbind();
}

void VertexArray::DrawArrays(const GLenum type, const GLint count){
	glDrawArrays(type, 0, count);
}

bool VertexArray::isBound() const{
	return bound;
}