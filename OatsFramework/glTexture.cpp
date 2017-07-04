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
	glDeleteTextures(1, &tex);
}

#include "flag.h"
#ifndef COMPATIBILITY_33
void glTexture::LoadImage(std::string path){
	img = IMG_Load(path.c_str());
	
	glTextureImage2DEXT(tex, GL_TEXTURE_2D, 0, GL_RGBA, img->w, img->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, img->pixels);
	glGenerateTextureMipmap(tex);
	if (img != nullptr)
		SDL_FreeSurface(img);
	fprintf(stderr, "glTexture : LoadImage called\n");
}
#endif
void glTexture::Bind(){
	bound = true;
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex);
}

void glTexture::Unbind(){
	bound = false;
	glBindTexture(GL_TEXTURE_2D, 0);
}
#ifndef COMPATIBILITY_33
void glTexture::SetFilter(GLenum filter){
	if (filter == GL_NEAREST | filter == GL_LINEAR){
		glTextureParameteri(tex, GL_TEXTURE_MAG_FILTER, filter);
		glTextureParameteri(tex, GL_TEXTURE_MIN_FILTER, filter);
	}
	else{
		assert(filter == GL_NEAREST | filter == GL_LINEAR);
	}
}

void glTexture::SetWrapMode(GLenum mode){
	glTextureParameteri(tex, GL_TEXTURE_WRAP_T, mode);
	glTextureParameteri(tex, GL_TEXTURE_WRAP_S, mode);
}

bool glTexture::IsBound() const{
	return bound;
}
#endif
#ifdef COMPATIBILITY_33
void glTexture::LoadImage(std::string path){
	img = IMG_Load(path.c_str());
	if (GLEW_EXT_direct_state_access){
		glTextureImage2DEXT(tex, GL_TEXTURE_2D, 0, GL_RGBA, img->w, img->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, img->pixels);
		glGenerateTextureMipmapEXT(tex, GL_TEXTURE_2D);
	}
	else{
		Bind();
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img->w, img->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, img->pixels);
		glGenerateMipmap(GL_TEXTURE_2D);
		Unbind();
	}
	if (img != nullptr)
		SDL_FreeSurface(img);
}

void glTexture::SetFilter(GLenum filter){
	if (GL_EXT_direct_state_access){
		glTextureParameteriEXT(tex, GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
		glTextureParameteriEXT(tex, GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
	}
	else{
		if (filter == GL_NEAREST | filter == GL_LINEAR){
			Bind();
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
			Unbind();
		}
		else{
			assert(filter == GL_NEAREST | filter == GL_LINEAR);
		}
	}
}

void glTexture::SetWrapMode(GLenum mode){
	if (GLEW_EXT_direct_state_access){
		glTextureParameteriEXT(tex, GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, mode);
		glTextureParameteriEXT(tex, GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, mode);
	}
	else{
		Bind();
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, mode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, mode);
		Unbind();
	}
}
#endif