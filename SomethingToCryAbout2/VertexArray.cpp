#include "VertexArray.h"


VertexArray::VertexArray()
{
	glGenVertexArrays(1, &vao);
}


VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &vao);
}

void VertexArray::Bind(){
	glBindVertexArray(vao);
}

void VertexArray::Unbind(){
	glBindVertexArray(0);
}

void VertexArray::Attrib(GLint index, GLint size, GLboolean normalized, int stride, int offset){
	Bind();
	glVertexAttribPointer(index, size, GL_FLOAT, normalized, sizeof(float)*stride, (void*)(sizeof(float)*offset));
	glEnableVertexAttribArray(index);
	Unbind();
}

void VertexArray::Draw(GLenum type, GLint count){
	Bind();
	glDrawArrays(type, 0, count);
	Unbind();
}