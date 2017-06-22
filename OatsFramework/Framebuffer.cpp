#include "Framebuffer.h"


Framebuffer::Framebuffer(int w, int h)
{
	glGenFramebuffers(1, &frameBufferObj);
	glGenRenderbuffers(1, &renderBufferObj);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferObj);
	glBindRenderbuffer(GL_RENDERBUFFER, renderBufferObj);
	glGenTextures(1, &texture);

	glBindTexture(GL_TEXTURE_2D, texture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, w, h);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBufferObj);
	isd_t = InternalScreenDimensions{ w, h };

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
		fprintf(stderr, "Framebuffer : Not complete");
		exit(0);
	}
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	isComplete = true;

	vbo.AddVertices(-1.0, 1.0); vbo.AddVertices(0.0, 1.0);
	vbo.AddVertices(-1.0, -1.0); vbo.AddVertices(0.0, 0.0);
	vbo.AddVertices(1.0, -1.0); vbo.AddVertices(1.0, 0.0);

	vbo.AddVertices(-1.0, 1.0); vbo.AddVertices(0.0, 1.0);
	vbo.AddVertices(1.0, -1.0); vbo.AddVertices(1.0, 0.0);
	vbo.AddVertices(1.0, 1.0); vbo.AddVertices(1.0, 1.0);

	vbo.BufferData();
	vbo.Bind();
	vao.Attrib(0, 4, false, 4, 0);
	vbo.Unbind();
}


Framebuffer::~Framebuffer()
{
	glDeleteTextures(1, &texture);
	glDeleteFramebuffers(1, &frameBufferObj);
	glDeleteRenderbuffers(1, &renderBufferObj);
}

void Framebuffer::Begin(){
	if (isComplete)
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferObj);
}

void Framebuffer::End(){
	if (isComplete)
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::Render(){
	glBindTexture(GL_TEXTURE_2D, texture);
	vao.Draw(GL_TRIANGLES, 6);
	glBindTexture(GL_TEXTURE_2D, 0);
}