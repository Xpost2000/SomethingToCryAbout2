#include "ShaderProgram.h"
#include "Shader.h"

ShaderProgram::ShaderProgram()
{
	sObject = glCreateProgram();
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(sObject);
}

void ShaderProgram::AddShader(Shader& sh){
	glAttachShader(this->sObject,sh.GetObject());
}

void ShaderProgram::DetachShader(Shader& sh){
	glDetachShader(sObject, sh.GetObject());
}

void ShaderProgram::LinkProgram(){
	glLinkProgram(sObject);
}

void ShaderProgram::Use(){
	glUseProgram(this->sObject);
}

/*
	I'm implementing all of these helper functions with direct state access cause it's
	more modern and oh shit. going to upgrade context version in a few minutes
*/
void ShaderProgram::SetUniform1i(const char* location, int v0){
	glProgramUniform1i(sObject, glGetUniformLocation(sObject, location), v0);
}
void ShaderProgram::SetUniform1f(const char* location, float v0){
	glProgramUniform1f(sObject, glGetUniformLocation(sObject, location), v0);
}
void ShaderProgram::SetUniform2f(const char* location, float v0, float v1){
	glProgramUniform2f(sObject, glGetUniformLocation(sObject, location), v0, v1);
}
void ShaderProgram::SetUniform3f(const char* location, float v0, float v1, float v2){
	glProgramUniform3f(sObject, glGetUniformLocation(sObject, location), v0, v1, v2);
}
void ShaderProgram::SetUniform4f(const char* location, float v0, float v1, float v2, float v3){
	glProgramUniform4f(sObject, glGetUniformLocation(sObject, location), v0, v1, v2, v3);
}

void ShaderProgram::SetUniform4fv(const char* location, float* value){
	glProgramUniform4fv(sObject, glGetUniformLocation(sObject, location), 1, &value[0]);
}
void ShaderProgram::SetUniformMatrix4fv(const char* location, float* value){
	glProgramUniformMatrix4fv(sObject, glGetUniformLocation(sObject, location), 1, false, &value[0]);
}