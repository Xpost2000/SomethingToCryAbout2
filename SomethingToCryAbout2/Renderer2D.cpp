#include "Renderer2D.h"


Renderer2D::Renderer2D(ShaderProgram *program)
{
	// Initialize everything
	this->program = program;
	buffer = new VertexBuffer();
	buffer->AddVertices(0.0, 1.0);
	buffer->AddVertices(0.0, 0.0);
	buffer->AddVertices(1.0, 1.0);
	buffer->AddVertices(1.0, 0.0);
	buffer->BufferData();
	buffer->Bind(); 
	vao = new VertexArray();
	vao->Attrib(0, 2, false, 2, 0);
	vao->Attrib(1, 2, false, 2, 0);
	buffer->Unbind();
	delete buffer;
}


Renderer2D::~Renderer2D()
{
	delete buffer;
	delete vao;
}

void Renderer2D::Draw(glm::vec2 pos, glm::vec2 size, float angle, glTexture *texture){
	program->Use();
	texture->Bind();
	model = glm::mat4();
	model = glm::translate(model, glm::vec3(pos, 1.0f));
	model = glm::scale(model, glm::vec3(size.x , size.y, 1.0f));
	program->SetUniform1i("textured", 1);
	program->SetUniform1i("tex", 0);
	program->SetUniformMatrix4fv("model", glm::value_ptr(model));
	vao->Draw(GL_TRIANGLE_STRIP, 4);
	texture->Unbind();
}

void Renderer2D::Draw(glm::vec2 pos, glm::vec2 size, float angle, glm::vec3 color){
	program->Use();
	model = glm::mat4();
	model = glm::translate(model, glm::vec3(pos, 1.0f));
	model = glm::scale(model, glm::vec3(size.x, size.y, 1.0f));
	program->SetUniform1i("textured", 0);
	program->SetUniform3f("iClr", color.r, color.g, color.b);
	program->SetUniformMatrix4fv("model", glm::value_ptr(model));
	vao->Draw(GL_TRIANGLE_STRIP, 4);
}

void Renderer2D::DrawM(glm::vec2 pos, glm::vec2 size, float angle, glTexture* texture, glm::vec3 color){
	program->Use();
	texture->Bind();
	model = glm::mat4();
	model = glm::translate(model, glm::vec3(pos, 1.0f));
	model = glm::scale(model, glm::vec3(size.x, size.y, 1.0f));
	program->SetUniform3f("iClr", color.r, color.g, color.b);
	program->SetUniform1i("textured", 2);
	program->SetUniform1i("tex", 0);
	program->SetUniformMatrix4fv("model", glm::value_ptr(model));
	vao->Draw(GL_TRIANGLE_STRIP, 4);
	texture->Unbind();
}

void Renderer2D::SupplyMatrix(glm::mat4& model){
	this->model = model;
}