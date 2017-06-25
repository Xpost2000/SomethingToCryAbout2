#pragma once
#include <map>
#include "Shader.h"
#include "glTexture.h"
#ifdef EXPERIMENTAL_FUNC
// Honestly for now it's just two functions.
// It's not even a proper resource manager
// It's just a placeholder for a full maanger
class ResourceManager
{
public:
	static bool LoadTexAsLinear;
	static bool LoadTexWrapRepeat;
	static glTexture* LoadTexture(std::string path);
	static Shader* LoadShader(std::string path, GLenum type);
};
#endif