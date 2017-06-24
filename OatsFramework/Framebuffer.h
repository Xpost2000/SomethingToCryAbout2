#pragma once
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "dllDef.h"
#include <GL\glew.h>

/*
	Framebuffer Class
	OpenGL wrapper effectively.

	Features a very simple and fairly clean interface to be used in.
	Little work is required since most of the initalization is handled in the constructor

	Functions 
	- Begin() // Binds this as the current framebuffer
	- End() // Unbind this frame buffer
	- Render() // Render a quad with the framebuffer texture
*/
class Framebuffer
{
public:
	// Constructor. Provide rendering width and height
	OATS_LIB_API Framebuffer(int w, int h);
	OATS_LIB_API ~Framebuffer();
	// Bind framebuffer
	OATS_LIB_API void Begin();
	// Unbind framebuffer
	OATS_LIB_API void End();
	// Render quad with texture
	OATS_LIB_API void Render();
private:
	bool isComplete = false;
	struct InternalScreenDimensions{
		int w, h;
	}isd_t;
	
	GLuint texture;
	GLuint renderBufferObj;
	GLuint frameBufferObj;
	VertexArray vao;
	VertexBuffer vbo;
};

