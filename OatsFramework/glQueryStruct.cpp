#include "glQueryStruct.h"
#include <cstring>
glQueryInfo QueryInformation(){
	glQueryInfo information;

	glGetIntegerv(GL_MAJOR_VERSION, &information.version.gl_version_major);
	glGetIntegerv(GL_MINOR_VERSION, &information.version.gl_version_minor);
	information.version.legacy.gl_api_version = const_cast<GLubyte*>(glGetString(GL_VERSION));
	information.vendor = const_cast<GLubyte*>(glGetString(GL_VENDOR));
	information.renderer = const_cast<GLubyte*>(glGetString(GL_RENDERER));
	glGetIntegerv(GL_NUM_EXTENSIONS, &information.ext_support_num);
	information.glsl_lang_version = const_cast<GLubyte*>(glGetString(GL_SHADING_LANGUAGE_VERSION));
	for (int i = 0; i < information.ext_support_num; i++){
		// The amount of C++ casts here is pretty scary.
		GLubyte* ext = const_cast<GLubyte*>(glGetStringi(GL_EXTENSIONS, i));
		information.extensionStrings.push_back(std::string(reinterpret_cast<char*>(ext)));
	}
	return information;
}

bool CheckExtension(std::string ext, const glQueryInfo a){
	for (int i = 0; i < a.ext_support_num; i++){
		// tbh not sure if it works
		const GLubyte* t = (GLubyte*)const_cast<char*>(a.extensionStrings[i].c_str());
		char* ExtType = "EXT (Vendor Extension)";
		if (strstr((const char*)t, "ARB") != NULL){
			ExtType = "ARB (Architecture Review Board Extension)";
		}
		else if (strstr((const char*)t, "INTEL") != NULL){
			ExtType = "INTEL Extension";
		}
		else if (strstr((const char*)t, "NV") != NULL){
			ExtType = "NV Extension (Nvidia)";
		}
		else if (strstr((const char*)t, "AMD") != NULL){
			ExtType = "AMD Extension (Advanced Micro Devices)";
		}
		else if (strstr((const char*)t, "MESA") != NULL){
			ExtType = "MESA Extension";
		}
		if (strcmp((const char*)t, ext.c_str()) == 0){
			printf("[%s Extension]%s:Extension Valid\n", ExtType,ext.c_str());
			return true;
		}
	}
	return false;
}

void PrintSupportedExtensions(const glQueryInfo a){
	for (auto& str : a.extensionStrings){
		printf("Extension : %s\n", str.c_str());
	}
}