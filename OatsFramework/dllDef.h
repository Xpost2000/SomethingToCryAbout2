#pragma once

#ifdef OATSFRAMEWORK_EXPORTS
#define OATS_LIB_API _declspec(dllexport)
#else
#define OATS_LIB_API _declspec(dllimport)
#endif

#define VERSION_RELEASE "0.001 Alpha"