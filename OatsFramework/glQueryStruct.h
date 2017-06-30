/*
	A struct that will contain the information for OpenGL querying.
*/
#include <GL\glew.h>
#include <vector>
#include "dllDef.h"
typedef struct 
{
	signed int ext_support_num;
	std::vector<std::string> extensionStrings;
	unsigned char* vendor;
	unsigned char* renderer;
	unsigned char* glsl_lang_version;
	struct __gl__namespace__version{
		struct ___legacy_struct_gl_api_version{
			unsigned char* gl_api_version;
		}legacy; // This is a cheap excuse for a namespace
		signed int gl_version_major;
		signed int gl_version_minor;
	}version;
}glQueryInfo;
/*
	Will return openGL query data
*/
OATS_LIB_API bool CheckExtension(std::string, const glQueryInfo);
OATS_LIB_API glQueryInfo QueryInformation();
OATS_LIB_API void PrintSupportedExtensions(const glQueryInfo);