#pragma once

#include <GL/glew.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

//Assert function to stop execution and highlight error during debugging
#define ASSERT(x) if (!(x)) __debugbreak();


//Error handling macros and functions

//#define DEBUG

#ifdef DEBUG
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x,__FILE__,__LINE__))
#else
#define GLCall(x) x
#endif

static void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

static void GLClearError() {
	while (glGetError() != GL_NO_ERROR);
}

static bool GLLogCall(const char* function, const char* file, int line) {

	while (GLenum error = glGetError()) {
		std::cout << "[OpenGL Error] (" << error << "): " << function << " " << file << " : " << line << std::endl;
		return false;
	}

	return true;
}