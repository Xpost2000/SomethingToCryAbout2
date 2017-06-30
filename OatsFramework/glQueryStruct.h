/*
	A struct that will contain the information for OpenGL querying.

	I just made this to check the OpenGL context status like the current version and stuff
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
	// Oh yeah. You cannot have namespaces in structs or classes so I went the cheap route
	// by making a struct to be a namespace.
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