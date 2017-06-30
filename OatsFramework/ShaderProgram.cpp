#include "ShaderProgram.h"
#include "Shader.h"

ShaderProgram::ShaderProgram()
{
	sObject = glCreateProgram();
	fprintf(stderr, "ShaderProgram : Shader Program Created\n");
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(sObject);
	fprintf(stderr, "ShaderProgram : Destructor\n");
}

void ShaderProgram::AddShader(Shader& sh){
	glAttachShader(this->sObject,sh.GetObject());
	fprintf(stderr, "ShaderProgram : Has been asked for Program Object\n");
}

void ShaderProgram::DetachShader(Shader& sh){
	glDetachShader(sObject, sh.GetObject());
	fprintf(stderr, "ShaderProgram : Shader detached from program.\n");
}

void ShaderProgram::LinkProgram(){
	glLinkProgram(sObject);
	fprintf(stderr, "ShaderProgram : Shader Program Linked\n");
}

void ShaderProgram::Use(){
	use = true;
	glUseProgram(this->sObject);
	fprintf(stderr, "ShaderProgram : Shader Program is now active\n");
}

bool ShaderProgram::isInUse() const{
	return use;
}

/*
	I may or may not downgrade this to be compatible with older OGL versions.
*/
#include "flag.h" // Use this flag to dictate whether it is openGL 3.3 compatible
#ifndef COMPATIBILITY_33
void ShaderProgram::SetUniform1i(const char* location, int v0){
	glProgramUniform1i(sObject, glGetUniformLocation(sObject, location), v0);
	fprintf(stderr, "ShaderProgram : Uniform1i set\n");
}
void ShaderProgram::SetUniform1f(const char* location, float v0){
	glProgramUniform1f(sObject, glGetUniformLocation(sObject, location), v0);
	fprintf(stderr, "ShaderProgram : Uniform1f set\n");
}
void ShaderProgram::SetUniform2f(const char* location, float v0, float v1){
	glProgramUniform2f(sObject, glGetUniformLocation(sObject, location), v0, v1);
	fprintf(stderr, "ShaderProgram : Uniform2f set\n");
}
void ShaderProgram::SetUniform3f(const char* location, float v0, float v1, float v2){
	glProgramUniform3f(sObject, glGetUniformLocation(sObject, location), v0, v1, v2);
	fprintf(stderr, "ShaderProgram : Uniform3f set\n");
}
void ShaderProgram::SetUniform4f(const char* location, float v0, float v1, float v2, float v3){
	glProgramUniform4f(sObject, glGetUniformLocation(sObject, location), v0, v1, v2, v3);
	fprintf(stderr, "ShaderProgram : Uniform4f set\n");
}

void ShaderProgram::SetUniform4fv(const char* location, float* value){
	glProgramUniform4fv(sObject, glGetUniformLocation(sObject, location), 1, &value[0]);
	fprintf(stderr, "ShaderProgram : Uniform4fv set\n");
}
void ShaderProgram::SetUniformMatrix4fv(const char* location, float* value){
	glProgramUniformMatrix4fv(sObject, glGetUniformLocation(sObject, location), 1, false, &value[0]);
	fprintf(stderr, "ShaderProgram : Uniform Matrix4fv set\n");
}
#endif
#ifdef COMPATIBILITY_33
// Pray to god you can support an extension cause rn I have no other work around

void ShaderProgram::SetUniform1i(const char* location, int v0){
	Use();
	glUniform1i(glGetUniformLocation(sObject, location), v0);
	fprintf(stderr, "ShaderProgram : Uniform1i set\n");
	Unuse();
}
void ShaderProgram::SetUniform1f(const char* location, float v0){
	Use();
	glUniform1f(glGetUniformLocation(sObject, location), v0);
	fprintf(stderr, "ShaderProgram : Uniform1f set\n");
	Unuse();
}
void ShaderProgram::SetUniform2f(const char* location, float v0, float v1){
	Use();
	glUniform2f(glGetUniformLocation(sObject, location), v0, v1);
	fprintf(stderr, "ShaderProgram : Uniform2f set\n");
	Unuse();
}
void ShaderProgram::SetUniform3f(const char* location, float v0, float v1, float v2){
	Use();
	glUniform3f(glGetUniformLocation(sObject, location), v0, v1, v2);
	fprintf(stderr, "ShaderProgram : Uniform3f set\n");
	Unuse();
}
void ShaderProgram::SetUniform4f(const char* location, float v0, float v1, float v2, float v3){
	Use();
	glUniform4f(glGetUniformLocation(sObject, location), v0, v1, v2, v3);
	fprintf(stderr, "ShaderProgram : Uniform4f set\n");
	Unuse();
}

void ShaderProgram::SetUniform4fv(const char* location, float* value){
	Use();
	glUniform4fv(glGetUniformLocation(sObject, location), 1, &value[0]);
	fprintf(stderr, "ShaderProgram : Uniform4fv set\n");
	Unuse();
}
void ShaderProgram::SetUniformMatrix4fv(const char* location, float* value){
	Use();
	glUniformMatrix4fv(glGetUniformLocation(sObject, location), 1, false, &value[0]);
	fprintf(stderr, "ShaderProgram : Uniform Matrix4fv set\n");
	Unuse();
}
#endif
void ShaderProgram::Unuse(){
	use = false;
	glUseProgram(0);
}
