#include "TextRenderer.h"


TextRenderer::TextRenderer(ShaderProgram* program)
{
	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6*4, (void*)0 , GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	sp = program;

	FT_Init_FreeType(&ftI);
}

void TextRenderer::LoadFont(std::string path, GLint fSize){
	FT_New_Face(ftI, path.c_str(), 0, &font);
	FT_Set_Pixel_Sizes(font, 0, fSize);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	for (GLubyte c = 0; c < 128; c++){
		GLuint texture;
		if (FT_Load_Char(font, c, FT_LOAD_RENDER)) { return; }
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0
					,GL_RED, font->glyph->bitmap.width,
							font->glyph->bitmap.rows,
							0,
							GL_RED,
							GL_UNSIGNED_BYTE,
							font->glyph->bitmap.buffer);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glBindTexture(GL_TEXTURE_2D, 0);
		Character temp = {
			texture,
			glm::ivec2(font->glyph->bitmap_left, font->glyph->bitmap_top),
			glm::ivec2(font->glyph->bitmap.width, font->glyph->bitmap.rows),
			font->glyph->advance.x
		};
		Characters.insert(std::pair<GLchar, Character>(c, temp));
		printf("Loaded Char %c\n", c);
	}
}

TextRenderer::~TextRenderer()
{
	FT_Done_FreeType(ftI);
	FT_Done_Face(font);
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
}

void TextRenderer::Render(std::string text, glm::vec2 pos, float scale, glm::vec3 rgb){
	sp->SetUniform1i("text", 0);
	sp->SetUniform3f("iClr", rgb.r, rgb.g, rgb.b);
	sp->Use();
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(vao);
	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++){
		Character ch = Characters[*c];
		float x = pos.x + ch.bearing.x * scale;
		float y = pos.y + (Characters['H'].bearing.y - ch.bearing.y) * scale;
		float w = ch.size.x * scale;
		float h = ch.size.y * scale;
		float verts[6][4] = {
			// tri 1
			{x, y+h, 0, 1},
			{x + w, y, 1, 0},
			{x, y, 0, 0},
			// tri 2
			{x, y +h, 0, 1},
			{x+w, y+h, 1, 1},
			{x+w, y, 1, 0}
		};
		glBindTexture(GL_TEXTURE_2D, ch.texture);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(verts), verts);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindTexture(GL_TEXTURE_2D, 0);
		pos.x += (ch.advance >> 6) * scale;
	}
	glBindVertexArray(0);
	sp->Unuse();
}