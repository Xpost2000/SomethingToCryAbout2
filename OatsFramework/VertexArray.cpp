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
	fprintf(stderr, "VertexArray : Bound VertexArray\n");
}

void VertexArray::Unbind(){
	bound = false;
	glBindVertexArray(0);
	fprintf(stderr, "VertexArray : Unbound Vertex Array\n");
}

void VertexArray::Attrib(GLint index, GLint size, GLboolean normalized, int stride, int offset){
	Bind();
	glVertexAttribPointer(index, size, GL_FLOAT, normalized, sizeof(float)*stride, (void*)(sizeof(float)*offset));
	glEnableVertexAttribArray(index);
	Unbind();
	fprintf(stderr, "VertexArray : Vertex Attribute Set\n");
}

void VertexArray::Draw(GLenum type, GLint count){
	Bind();
	glDrawArrays(type, 0, count);
	Unbind();
	fprintf(stderr, "VertexArray : Drawing contents.\n");
}

void VertexArray::DrawArrays(GLenum type, GLint count){
	glDrawArrays(type, 0, count);
}

bool VertexArray::isBound() const{
	return bound;
}