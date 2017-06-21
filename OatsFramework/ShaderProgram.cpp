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
	glUseProgram(this->sObject);
	fprintf(stderr, "ShaderProgram : Shader Program is now active\n");
}

/*
	I'm implementing all of these helper functions with direct state access cause it's
	more modern and oh shit. going to upgrade context version in a few minutes
*/
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

void ShaderProgram::Unuse(){
	glUseProgram(0);
}