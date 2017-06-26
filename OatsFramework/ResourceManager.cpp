#include "ResourceManager.h"
#ifdef EXPERIMENTAL_FUNC
bool ResourceManager::LoadTexAsLinear = false;
bool ResourceManager::LoadTexWrapRepeat = true;
std::map< std::string, glTexture > ResourceManager::Textures;
std::map< std::string, Shader > ResourceManager::Shaders;
glTexture ResourceManager::LoadTexture(std::string path, std::string key){
	glTexture tex;
	if (!LoadTexAsLinear){
		tex.SetFilter(GL_NEAREST);
	}
	else{
		tex.SetFilter(GL_LINEAR);
	}
	if (!LoadTexWrapRepeat){
		tex.SetWrapMode(GL_CLAMP_TO_EDGE);
	}
	else{
		tex.SetWrapMode(GL_REPEAT);
	}
	tex.LoadImage(path);
	//Textures.insert(std::pair<std::string, glTexture>(key, tex));
	Textures[key] = tex;
	return tex;
}

Shader ResourceManager::LoadShader(std::string path, GLenum type, std::string key){
	Shader shader(type);
	shader.LoadFromFile(path);
	Shaders.insert(std::pair<std::string, Shader>(key, shader));
	return shader;
}

Shader ResourceManager::GetShader(std::string key){
	return Shaders.find(key)->second;
}

glTexture ResourceManager::GetTexture(std::string key){
	return Textures[key];
}

#endif