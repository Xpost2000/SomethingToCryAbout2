#pragma once
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "glTexture.h"
#include "ShaderProgram.h"
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
	OATS_LIB_API void Draw(glm::vec2 pos, glm::vec2 size, float angle, glTexture *texture);
	// Colored rectangle draw + 1 overload
	OATS_LIB_API void Draw(glm::vec2 pos, glm::vec2 size, float angle, glm::vec3 color = glm::vec3(255, 255, 255));
	// Colored Rectangle with texture
	OATS_LIB_API void DrawM(glm::vec2 pos, glm::vec2 size, float angle, glTexture *texture, glm::vec3 color = glm::vec3(255, 255, 255));
	OATS_LIB_API void EnableAlpha(bool);
	OATS_LIB_API void EnableAntiAliasing(bool);
private:
	glm::mat4 model; // matrix

	ShaderProgram* program;
	VertexBuffer* buffer;
	VertexArray* vao;
};

