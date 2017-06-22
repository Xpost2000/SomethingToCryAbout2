#pragma once
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "dllDef.h"
#include <GL\glew.h>

class Framebuffer
{
public:
	OATS_LIB_API Framebuffer(int w, int h);
	OATS_LIB_API ~Framebuffer();
	OATS_LIB_API void Begin();
	OATS_LIB_API void End();
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

