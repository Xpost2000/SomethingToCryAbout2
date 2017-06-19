#pragma once
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "glTexture.h"
#include "ShaderProgram.h"
#include "MathHelperFunctions.h"

class Renderer2D
{
public:
	Renderer2D(ShaderProgram *program);
	~Renderer2D();
	void SupplyMatrix(glm::mat4 &model);
	void Draw(glm::vec2 pos, glm::vec2 size, float angle, glTexture *texture);
	// Colored rectangle draw + 1 overload
	void Draw(glm::vec2 pos, glm::vec2 size, float angle, glm::vec3 color = glm::vec3(255, 255, 255));
	// Colored Rectangle with texture
	void DrawM(glm::vec2 pos, glm::vec2 size, float angle, glTexture *texture, glm::vec3 color = glm::vec3(255, 255, 255));
	void EnableAlpha(bool);
private:
	glm::mat4 model; // matrix

	ShaderProgram* program;
	VertexBuffer* buffer;
	VertexArray* vao;
};

