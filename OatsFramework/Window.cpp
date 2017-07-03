#include "Window.h"
#include "flag.h"
#include <gl\glew.h>
Window::Window(char* name, int w, int h){
	this->w = w;
	this->h = h;
	this->name = name;
	// Initialize default variables
}

Window::Window() : Window("Default", 500, 500)
{
}

void Window::ShouldClose(bool val){
	bShouldClose = val;
}

bool Window::GetShouldClose(){
	return bShouldClose;
}

Window::~Window()
{
	SDL_GL_DeleteContext(ogl);
	SDL_DestroyWindow(window);
}

void Window::CreateWindow(){
	window = SDL_CreateWindow(name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
#ifdef COMPATIBILITY_33
	SDL_GL_SetAttribute(SDL_GLattr::SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GLattr::SDL_GL_CONTEXT_MINOR_VERSION, 3);
#endif
#ifndef COMPATIBILITY_33
	SDL_GL_SetAttribute(SDL_GLattr::SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GLattr::SDL_GL_CONTEXT_MINOR_VERSION, 5);
#endif
	SDL_GL_SetAttribute(SDL_GLattr::SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GLattr::SDL_GL_BUFFER_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GLattr::SDL_GL_STENCIL_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GLattr::SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GLattr::SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GLattr::SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GLattr::SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GLattr::SDL_GL_ACCELERATED_VISUAL, 1);
	SDL_GL_SetAttribute(SDL_GLattr::SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GLattr::SDL_GL_MULTISAMPLESAMPLES, 8);
	ogl = SDL_GL_CreateContext(window);
	glewExperimental = true;
	if (glewInit() == GLEW_OK) { 
	}
	else { SDL_Quit(); exit(0); }
}

void Window::Refresh(){
	SDL_GL_SwapWindow(window);
}

SDL_Window* Window::returnWindowHandle(){
	return window;
}