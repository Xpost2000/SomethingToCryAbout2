#pragma once
#include <fstream>
#include "dllDef.h"
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2\SDL_image.h>
/*
	glTexture

	OpenGL texture wrapper class. Handles most of the initalization and hard work in the constructor.
	This texture class is ment to be taking pixel data from an image.
	You still have a fair amount of control with the object and if you wish you can retrieve the 
	handle directly to edit with lower level functions
*/
class glTexture
{
public:
	OATS_LIB_API glTexture();
	OATS_LIB_API ~glTexture();
	OATS_LIB_API void Bind(); 
	OATS_LIB_API void Unbind();
	OATS_LIB_API bool IsBound() const;
	// Load an image from specified path
	OATS_LIB_API void LoadImage(std::string path);
	// Set texture mag and min filters. GL_LINEAR or GL_NEAREST accepted
	OATS_LIB_API void SetFilter(GLenum filter);
	// Set texture wrapping mode. GL_REPEAT / GL_CLAMP_TO ___ accepted
	OATS_LIB_API void SetWrapMode(GLenum mode);
	// Retrieve texture object handle
	OATS_LIB_API inline GLuint GetTextureObject() { return tex; }
private:
	bool bound;
	GLuint tex;
	SDL_Surface* img = nullptr;
};

