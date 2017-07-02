#pragma once
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "glTexture.h"
#include "ShaderProgram.h"
#include "Shader.h"
#include "MathHelperFunctions.h"

/*
	Renderer2D

	This is a basic 2D renderer.
	It contains it's own model matrix which most be supplied from an original matrix.
	It has the capacity to Render 3 types of things

	Textured Objects
	Colored Objects
	Textured Objects with Additive Blend Colors.

	It also has alpha enabling as a choice.
	ShaderProgram MUST be specified as a constructor argument.
*/
class Renderer2D
{
public:
	OATS_LIB_API Renderer2D(ShaderProgram *program);
	OATS_LIB_API ~Renderer2D();
	OATS_LIB_API void SupplyMatrix(glm::mat4 &model);
	OATS_LIB_API void Begin(glTexture &tex, glm::vec3 color);
	OATS_LIB_API void Begin();
	OATS_LIB_API void End();
	OATS_LIB_API void End(glTexture &tex);
	OATS_LIB_API void Draw(glm::vec2 pos, glm::vec2 size, float angle);
	// Colored rectangle draw + 1 overload
	OATS_LIB_API void DrawRect(glm::vec2 pos, glm::vec2 size, float angle);
	void SetColor(glm::vec3 clr) { program->SetUniform3f("iClr", clr.r, clr.g, clr.b); }
	OATS_LIB_API void EnableAlpha(bool);
	OATS_LIB_API void EnableAntiAliasing(bool);
	OATS_LIB_API void EnableWireFrame(bool);
	OATS_LIB_API void EnablePointsDraw(bool);
	OATS_LIB_API void SetPointSize(int);
	OATS_LIB_API void SetLineSize(int);
	// Manually swap and handle textures
	void BindTexture(glTexture & tex) { tex.Bind(); }
	void UnbindTexture(glTexture & tex) { tex.Unbind(); }
private:
	glm::mat4 model; // matrix

	ShaderProgram* program;
	VertexBuffer* buffer;
	VertexArray* vao;
};

