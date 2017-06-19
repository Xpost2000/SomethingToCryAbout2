#include "Shader.h"
#include <fstream>
#include <sstream>
#include <cassert>
Shader::Shader(GLenum sh)
{
	if (sh == GL_FRAGMENT_SHADER | sh == GL_GEOMETRY_SHADER | sh == GL_VERTEX_SHADER)
		shaderObject = glCreateShader(sh); // Start with shader creation
	else
		assert(sh == GL_FRAGMENT_SHADER | sh == GL_GEOMETRY_SHADER | sh == GL_VERTEX_SHADER);
}


Shader::~Shader()
{
	glDeleteShader(shaderObject);
}

void Shader::LoadFromFile(std::string path){
	std::ifstream file(path);
	std::stringstream ss;
	ss << file.rdbuf();
	std::string str = ss.str();
	const char* code = str.c_str();
	::printf("%s\n", code);
	glShaderSource(shaderObject, 1, &code, 0);
	glCompileShader(shaderObject);
}

void Shader::LoadFromSource(char* code){
	glShaderSource(shaderObject, 1, &code, 0);
	glCompileShader(shaderObject);
}