#pragma once
#include <GL/glew.h>
class VertexArray
{
public:
	VertexArray();
	~VertexArray();
	void Bind();
	void Unbind();
	void Attrib(GLint index, GLint size, GLboolean normalized, int stride, int offset);
	void Draw(GLenum type, GLint count);
private:
	GLuint vao;
};

