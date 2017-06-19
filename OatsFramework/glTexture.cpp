#include "glTexture.h"
#include <cassert>

glTexture::glTexture()
{
	glGenTextures(1, &tex);
	fprintf(stderr, "glTexture : Created Instance\n");
}


glTexture::~glTexture()
{
	fprintf(stderr, "glTexture : Destructor\n");
	SDL_FreeSurface(img);
	glDeleteTextures(1, &tex);
}

void glTexture::LoadImage(std::string path){
	img = IMG_Load(path.c_str());
	glTextureImage2DEXT(tex, GL_TEXTURE_2D, 0, GL_RGBA, img->w, img->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, img->pixels);
	glGenerateTextureMipmap(tex);
	fprintf(stderr, "glTexture : LoadImage called\n");
}

void glTexture::Bind(){
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex);
	fprintf(stderr, "glTexture : Bound Texture\n");
}

void glTexture::Unbind(){
	glBindTexture(GL_TEXTURE_2D, 0);
	fprintf(stderr, "glTexture : Unbound Texture\n");
}

void glTexture::SetFilter(GLenum filter){
	if (filter == GL_NEAREST | filter == GL_LINEAR){
		glTextureParameteri(tex, GL_TEXTURE_MAG_FILTER, filter);
		glTextureParameteri(tex, GL_TEXTURE_MIN_FILTER, filter);
		fprintf(stderr, "glTexture : Texture Filtering Set\n");
	}
	else{
		assert(filter == GL_NEAREST | filter == GL_LINEAR);
	}
}

void glTexture::SetWrapMode(GLenum mode){
	glTextureParameteri(tex, GL_TEXTURE_WRAP_T, mode);
	glTextureParameteri(tex, GL_TEXTURE_WRAP_S, mode);
	fprintf(stderr, "glTexture : Texture Wrapping Mode Set\n");
}