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
#endif
#ifdef COMPATIBILITY_33
/*
	Most of this code is sadly unreliable mostly because my framework for the most part
	relies on Direct State Access taking care of all the work I need.

	I used a "emulated" DSA style setup.
	I first attempt to use an extension. If it is not supported then we do the fallback which is a sort of
	DSA setup
*/
void ShaderProgram::SetUniform1i(const char* location, int v0){
	if (GLEW_EXT_direct_state_access){ // this is the extension
		glProgramUniform1iEXT(sObject, glGetUniformLocation(sObject, location), v0);
	}
	else{
		// If extension doesn't work
		if (!isInUse())
		Use();
		glUniform1i(glGetUniformLocation(sObject, location), v0);
	//	Unuse();
	}
}
void ShaderProgram::SetUniform1f(const char* location, float v0){
	if (GLEW_EXT_direct_state_access){
		glProgramUniform1fEXT(sObject, glGetUniformLocation(sObject, location), v0);
	}
	else{
		if (!isInUse())
		Use();
		glUniform1f(glGetUniformLocation(sObject, location), v0);
		//	Unuse();
	}
}
void ShaderProgram::SetUniform2f(const char* location, float v0, float v1){
		if (GLEW_EXT_direct_state_access){
			glProgramUniform2fEXT(sObject, glGetUniformLocation(sObject, location), v0, v1);
		}
		else{
		if (!isInUse()){
			Use();
		}
		glUniform2f(glGetUniformLocation(sObject, location), v0, v1);
		//	Unuse();
	}
}
void ShaderProgram::SetUniform3f(const char* location, float v0, float v1, float v2){
	if (GLEW_EXT_direct_state_access){
		glProgramUniform3fEXT(sObject, glGetUniformLocation(sObject, location), v0, v1, v2);
	}
	else{
		Use();
		glUniform3f(glGetUniformLocation(sObject, location), v0, v1, v2);
		//	Unuse();
	}
}
void ShaderProgram::SetUniform4f(const char* location, float v0, float v1, float v2, float v3){
	if (GLEW_EXT_direct_state_access){
		glProgramUniform4fEXT(sObject, glGetUniformLocation(sObject, location), v0, v1, v2, v3);
	}
	else{
		Use();
		glUniform4f(glGetUniformLocation(sObject, location), v0, v1, v2, v3);
		//	Unuse();
	}
}

void ShaderProgram::SetUniform4fv(const char* location, float* value){
	if (GLEW_EXT_direct_state_access){
		glProgramUniform4fvEXT(sObject, glGetUniformLocation(sObject, location), 1, &value[0]);
	}
	else{
		Use();
		glUniform4fv(glGetUniformLocation(sObject, location), 1, &value[0]);
		//	Unuse();
	}
}
void ShaderProgram::SetUniformMatrix4fv(const char* location, float* value){
	if (GLEW_EXT_direct_state_access){
		glProgramUniformMatrix4fvEXT(sObject, glGetUniformLocation(sObject, location), 1, false, &value[0]);
	}
	else{
		Use();
		glUniformMatrix4fv(glGetUniformLocation(sObject, location), 1, false, &value[0]);
		//	Unuse();
	}
}
#endif
void ShaderProgram::Unuse(){
	use = false;
	glUseProgram(0);
}
