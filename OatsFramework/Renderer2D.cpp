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

void Renderer2D::Draw(glm::vec2 pos, glm::vec2 size, float angle){
	model = glm::mat4();
	model = glm::translate(model, glm::vec3(pos, 1.0f));
	model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
	model = glm::rotate(model, angle, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));
	model = glm::scale(model, glm::vec3(size.x, size.y, 1.0f));
	program->SetUniform1i("textured", 2);
	program->SetUniform1i("tex", 0);
	program->SetUniformMatrix4fv("model", glm::value_ptr(model));
	vao->DrawArrays(GL_TRIANGLE_STRIP, 4);
}

void Renderer2D::DrawWater(glm::vec2 pos, glm::vec2 size, float angle){
	model = glm::mat4();
	model = glm::translate(model, glm::vec3(pos, 1.0f));
	model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
	model = glm::rotate(model, angle, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));
	model = glm::scale(model, glm::vec3(size.x, size.y, 1.0f));
	program->SetUniform1i("textured", 3);
	program->SetUniform1i("tex", 0);
	program->SetUniformMatrix4fv("model", glm::value_ptr(model));
	vao->DrawArrays(GL_TRIANGLE_STRIP, 4);
}

void Renderer2D::DrawRect(glm::vec2 pos, glm::vec2 size, float angle){
	model = glm::mat4();
	model = glm::translate(model, glm::vec3(pos, 1.0f));
	model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
	model = glm::rotate(model, angle, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));
	model = glm::scale(model, glm::vec3(size.x, size.y, 1.0f));
	program->SetUniform1i("textured", 0);
	program->SetUniformMatrix4fv("model", glm::value_ptr(model));

	vao->DrawArrays(GL_TRIANGLE_STRIP, 4);
}

void Renderer2D::SupplyMatrix(glm::mat4& model){
	this->model = model;
}

void Renderer2D::EnableAlpha(bool val){
	if (val){
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	else{
		return;
	}
}

void Renderer2D::EnableAntiAliasing(bool val){
	if (val){
		glEnable(GL_MULTISAMPLE);
	}
	else{
		return;
	}
}

void Renderer2D::EnableWireFrame(bool val){
	if (val){
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		return;
	}
}

void Renderer2D::EnablePointsDraw(bool val){
	if (val){
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	}
	else{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		return;
	}
}

void Renderer2D::SetPointSize(const float size){
	glPointSize(size);
}

void Renderer2D::SetLineSize(const float size){
	glLineWidth(size);
}

// This minor change improves performance on unlocked fps. (300 increase for me)
void Renderer2D::Begin(glTexture& tex, glm::vec3 color){
	if (!vao->isBound())
	vao->Bind();
	tex.Bind();	
	program->SetUniform3f("iClr", color.r, color.g, color.b);
	if (!program->isInUse())
		program->Use();
}

void Renderer2D::End(glTexture& tex){
	if (vao->isBound())
	vao->Unbind();
	tex.Unbind();
	if (program->isInUse())
		program->Unuse();
}

void Renderer2D::Begin(){
	if (!vao->isBound())
		vao->Bind();
	if (!program->isInUse())
		program->Use();
}

void Renderer2D::End(){
	if (vao->isBound())
		vao->Unbind();
	if (program->isInUse())
		program->Unuse();
}

void Renderer2D::SetProgram(ShaderProgram* program){
	program->Use();
}

void Renderer2D::ResetProgram(){
	program->Use();
}

void Renderer2D::PassInUniform(const char* uni, float v0){
	program->SetUniform1f(uni, v0);
}

void Renderer2D::PassInUniform(ShaderProgram* program, const char* uni, float v0){
	program->SetUniform1f(uni, v0);
}

void Renderer2D::SendAllUniformsTo(ShaderProgram* program){
	program->SetUniform1i("textured", 2);
	program->SetUniform1i("tex", 0);
	program->SetUniformMatrix4fv("model", glm::value_ptr(model));
}