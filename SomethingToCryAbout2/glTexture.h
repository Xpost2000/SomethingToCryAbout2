#pragma once
#include <fstream>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2\SDL_image.h>
class glTexture
{
public:
	glTexture();
	~glTexture();
	void Bind(); void Unbind();
	void LoadImage(std::string path);
	void SetFilter(GLenum filter);
	void SetWrapMode(GLenum mode);
private:
	GLuint tex;
	SDL_Surface* img;
};

