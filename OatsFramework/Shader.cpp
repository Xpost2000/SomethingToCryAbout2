#include "Shader.h"
#include <fstream>
#include <sstream>
#include <cassert>
Shader::Shader(GLenum sh)
{
	if (sh == GL_FRAGMENT_SHADER | sh == GL_GEOMETRY_SHADER | sh == GL_VERTEX_SHADER){
		shaderObject = glCreateShader(sh); // Start with shader creation
		if (sh == GL_FRAGMENT_SHADER){
			fprintf(stderr, "Shader Class : Created Shader Type FRAGMENT\n");
		}
		else if (sh == GL_GEOMETRY_SHADER){
			fprintf(stderr, "Shader Class : Created Shader Type GEOMETRY\n");
		}
		else{
			fprintf(stderr, "Shader Class : Created Shader Type VERTEX\n");
		}
	}
	else{
		fprintf(stderr, "Shader Class : Assertion Created : NOT EQUAL TO ENUM TYPE\n");
		assert(sh == GL_FRAGMENT_SHADER | sh == GL_GEOMETRY_SHADER | sh == GL_VERTEX_SHADER);
	}
}


Shader::~Shader()
{
	fprintf(stderr, "Shader Class : Destructor Called\n");
	glDeleteShader(shaderObject);
}

void Shader::LoadFromFile(std::string path){
	std::ifstream file(path);
	std::stringstream ss;
	ss << file.rdbuf();
	std::string str = ss.str();
	fprintf(stderr, "Shader Class : Loaded Shader\n");
	const char* code = str.c_str();
	glShaderSource(shaderObject, 1, &code, 0);
	glCompileShader(shaderObject);
	fprintf(stderr, "Shader Class : Compiled Shader\n");
}

void Shader::LoadFromSource(char* code){
	fprintf(stderr, "Shader Class : Loaded Shader (From Source)\n");
	glShaderSource(shaderObject, 1, &code, 0);
	glCompileShader(shaderObject);
	fprintf(stderr, "Shader Class : Compiled Shader\n");
}