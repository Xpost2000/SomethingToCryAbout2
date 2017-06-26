#pragma once
#include "dllDef.h"
#include <map>
#include <string>
#include "ShaderProgram.h" // Do this later
#include "Shader.h"
#include "glTexture.h"
#define EXPERIMENTAL_FUNC
#ifdef EXPERIMENTAL_FUNC
// Honestly for now it's just two functions.
// It's not even a proper resource manager
// It's just a placeholder for a full maanger
class ResourceManager
{
public:
	static std::map<std::string, glTexture> Textures;
	static std::map<std::string, Shader> Shaders;
	static bool LoadTexAsLinear;
	static bool LoadTexWrapRepeat;
	OATS_LIB_API static glTexture LoadTexture(std::string path, std::string key);
	OATS_LIB_API static Shader LoadShader(std::string path, GLenum type, std::string key);
	OATS_LIB_API static Shader GetShader(std::string key);
	OATS_LIB_API static glTexture GetTexture(std::string key);
};
#endif