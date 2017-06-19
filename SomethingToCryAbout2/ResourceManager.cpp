#include "ResourceManager.h"
#ifdef EXPERIMENTAL_FUNC
bool ResourceManager::LoadTexAsLinear = false;
bool ResourceManager::LoadTexWrapRepeat = true;

glTexture* ResourceManager::LoadTexture(std::string path){
	glTexture *tex = new glTexture();
	if (!LoadTexAsLinear){
		tex->SetFilter(GL_NEAREST);
	}
	else{
		tex->SetFilter(GL_LINEAR);
	}
	if (!LoadTexWrapRepeat){
		tex->SetWrapMode(GL_CLAMP_TO_EDGE);
	}
	else{
		tex->SetWrapMode(GL_REPEAT);
	}
	tex->LoadImage(path);
	return tex;
}

Shader* ResourceManager::LoadShader(std::string path, GLenum type){
	Shader shader(type);
	shader.LoadFromFile(path);
	return &shader;
}
#endif