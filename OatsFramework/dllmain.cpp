#include <Windows.h>
#include <cstdio>
#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>
#include "dllDef.h"
#include <ctime>
#include <ft2build.h>
#include FT_FREETYPE_H
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	freopen("Oats_stderr.log", "a", stderr);
	// Calculate Time Frame
	time_t date = time(NULL);
	tm *t = localtime(&date);
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		fprintf(stderr, "File Redirection : STDERR\n");
		fprintf(stderr, "Log Timestamp : %d\\%d\\%d		%d hrs: %d mins: %d secs\n", t->tm_mon+1, t->tm_mday+1, t->tm_year+1900, t->tm_hour+1, t->tm_min+1, t->tm_sec+1);
		fprintf(stderr ,"This Game is running the Oats Framework v%s\n------------------------------------", VERSION_RELEASE);
		fprintf(stderr,"\nOatsframework : Process Attach\n");
		if (SDL_Init(SDL_INIT_VIDEO) != 0){
			fprintf(stderr, "SDL_ERROR : %s\n", SDL_GetError());
			exit(1);
		}
		else{
			fprintf(stderr, "SDL_INIT : Init Success\n");
		}
		if (!IMG_Init(IMG_INIT_PNG)){
			fprintf(stderr, "SDL_IMG_ERROR : %s\n", IMG_GetError());
			exit(1);
		}
		else{
			fprintf(stderr, "SDL_IMG : Init Success\n");
		}
		
		MessageBoxA(NULL, "This framework is in very early alpha", "Please leave advice and or criticism", MB_ICONINFORMATION);
		fprintf(stderr, "Warning Message Displayed\n");
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		fprintf(stderr, "\nEngine Quit\n");
		fclose(stderr);
		IMG_Quit();
		SDL_Quit();
		break;
	}
	return TRUE;
}

