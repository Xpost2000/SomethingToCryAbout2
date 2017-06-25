#pragma once
#include <map>
#include "dllDef.h"
#include <gl\glew.h>
#include <ft2build.h>
#include <glm\glm.hpp>
#include <string>
#include "ShaderProgram.h"
#include FT_FREETYPE_H
// Make a generic renderer class first then implement
// text rendering

// Freetype convience wrapper
struct Character{
	GLuint texture;
	glm::ivec2 bearing;
	glm::ivec2 size;
	int advance;
};

class TextRenderer
{
public:
	OATS_LIB_API TextRenderer(ShaderProgram* program);
	OATS_LIB_API ~TextRenderer();
	OATS_LIB_API void Render(std::string text, glm::vec2 pos, float scale, glm::vec3 rgb);
	OATS_LIB_API void LoadFont(std::string path, GLint fSize);
private: 
	GLuint vbo;
	GLuint vao;
	FT_Library ftI; // sadly I couldn't think of a better way. each instance of text renderer has it's own instance of freeType
	FT_Face font;
	ShaderProgram* sp;
	std::map<GLchar, Character> Characters;
};

