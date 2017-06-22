#pragma once
#include <fstream>
#include "dllDef.h"
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2\SDL_image.h>
class glTexture
{
public:
	OATS_LIB_API glTexture();
	OATS_LIB_API ~glTexture();
	OATS_LIB_API void Bind(); 
	OATS_LIB_API static void Unbind();
	OATS_LIB_API void LoadImage(std::string path);
	OATS_LIB_API void SetFilter(GLenum filter);
	OATS_LIB_API void SetWrapMode(GLenum mode);
	OATS_LIB_API void Allocate(GLenum fmt, int w, int h);
	OATS_LIB_API inline GLuint GetTextureObject() { return tex; }
private:
	GLuint tex;
	SDL_Surface* img = nullptr;
};

