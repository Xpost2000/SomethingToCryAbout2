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
	fprintf(stderr, "Renderer2D : Instance Created\n");
	delete buffer;
}


Renderer2D::~Renderer2D()
{
	fprintf(stderr, "Renderer2D : Destructor\n");
	delete buffer;
	delete vao;
}

void Renderer2D::Draw(glm::vec2 pos, glm::vec2 size, float angle, glTexture &texture){
	texture.Bind();
	model = glm::mat4();
	model = glm::translate(model, glm::vec3(pos, 1.0f));
	model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
	model = glm::rotate(model, angle, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));
	model = glm::scale(model, glm::vec3(size.x, size.y, 1.0f));
	program->SetUniform1i("textured", 1);
	program->SetUniform1i("tex", 0);
	program->SetUniformMatrix4fv("model", glm::value_ptr(model));
	program->Use();
	vao->Draw(GL_TRIANGLE_STRIP, 4);
	texture.Unbind();
	fprintf(stderr, "Renderer2D: Draw Quad (Overload +1)\n");
	program->Unuse();
}

void Renderer2D::Draw(glm::vec2 pos, glm::vec2 size, float angle, glm::vec3 color){
	model = glm::mat4();
	model = glm::translate(model, glm::vec3(pos, 1.0f));
	model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
	model = glm::rotate(model, angle, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));
	model = glm::scale(model, glm::vec3(size.x, size.y, 1.0f));
	program->SetUniform1i("textured", 0);
	program->SetUniform3f("iClr", color.r, color.g, color.b);
	program->SetUniformMatrix4fv("model", glm::value_ptr(model));
	program->Use();
	vao->Draw(GL_TRIANGLE_STRIP, 4);
	program->Unuse();
	fprintf(stderr, "Renderer2D: Draw Quad(Overload +2)\n");
}

void Renderer2D::DrawM(glm::vec2 pos, glm::vec2 size, float angle, glTexture& texture, glm::vec3 color){
	texture.Bind();
	model = glm::mat4();
	model = glm::translate(model, glm::vec3(pos, 1.0f));

	model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
	model = glm::rotate(model, angle, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));
	model = glm::scale(model, glm::vec3(size.x, size.y, 1.0f));
	program->SetUniform3f("iClr", color.r, color.g, color.b);
	program->SetUniform1i("textured", 2);
	program->SetUniform1i("tex", 0);
	program->SetUniformMatrix4fv("model", glm::value_ptr(model));
	program->Use();
	vao->Draw(GL_TRIANGLE_STRIP, 4);
	texture.Unbind();
	program->Unuse();
	fprintf(stderr, "Renderer2D: Draw Quad(Overload +3)\n");
}

void Renderer2D::SupplyMatrix(glm::mat4& model){
	this->model = model;
	fprintf(stderr, "Renderer2D: Model Matrix Supplied.\n");
}

void Renderer2D::EnableAlpha(bool val){
	if (val){
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		fprintf(stderr, "Renderer2D: Alpha has been Enabled\n");
	}
	else{
		return;
	}
}

void Renderer2D::EnableAntiAliasing(bool val){
	if (val){
		glEnable(GL_MULTISAMPLE);
		fprintf(stderr, "Renderer2D: Anti-Aliasing Functionality Enabled\n");
	}
	else{
		return;
	}
}