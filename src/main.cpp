#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Error.h"
#include "Shaders.h"
#include "Rectangle.h"

/*Basic OpenGL setup code
Draws rounded rectangle*/


int main(int, char**)
{

	// Setup window
	glfwSetErrorCallback(glfw_error_callback);
	if (!glfwInit())
		return 1;

	//Setup window with OpenGL 3.3 Version using Core Profile

	//const char* glsl_version = "#version 130";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create window with graphics context
	GLFWwindow* window = glfwCreateWindow(1280, 720, "Syncode GUI", NULL, NULL);
	if (window == NULL)
		return 1;
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // Enable vsync - limits to screen refresh rate


	//Check for any errors so far
	bool err = glewInit() != GLEW_OK;

	if (err)
	{
		fprintf(stderr, "Failed to initialize OpenGL loader!\n");
		return 1;
	}


	
	createRectangleShader();
	//setRectangleVertices();

	Rectangle r1;

	Camera::GetInstance()->setPosition(glm::vec3(640.0f, 360.0f, 0.0f));
	glfwSetKeyCallback(window, Camera::GetInstance()->key_callback);

	// Main loop
	while (!glfwWindowShouldClose(window))
	{

		//This waits for user input or updates after 1.0 secs
		glfwWaitEventsTimeout(1.0f);

		//TODO: Not sure if viewport is depecrated or not
		//GLCall(glViewport(0, 0, display_w, display_h));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		Camera::GetInstance()->update();

		r1.render();

		//Swap forward and backward buffer
		glfwSwapBuffers(window);

	}

	deleteRectangleShader();

	//Cleanup
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
