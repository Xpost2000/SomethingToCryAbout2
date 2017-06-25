#include "glQueryStruct.h"

glQueryInfo QueryInformation(){
	glQueryInfo information;

	glGetIntegerv(GL_MAJOR_VERSION, &information.version.gl_version_major);
	glGetIntegerv(GL_MINOR_VERSION, &information.version.gl_version_minor);
	information.version.legacy.gl_api_version = const_cast<GLubyte*>(glGetString(GL_VERSION));
	information.vendor = const_cast<GLubyte*>(glGetString(GL_VENDOR));
	information.renderer = const_cast<GLubyte*>(glGetString(GL_RENDERER));
	information.ext_support_num = 0; // Querying for extensions causes crash.
	information.glsl_lang_version = const_cast<GLubyte*>(glGetString(GL_SHADING_LANGUAGE_VERSION));
	return information;
}