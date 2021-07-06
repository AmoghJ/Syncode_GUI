#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include <chrono>

#include <GL/glew.h>
#include <GLFW/glfw3.h>


#include "Error.h"
#include "Shaders.h"
#include "Camera.h"
#include "RectangleRenderer.h"
#include "Rectangle.h"

#include "gtc/random.hpp"
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

	//Enable blending for transparent pixels
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	//setRectangleVertices();

	std::vector<Rectangle*> rects;

	for (int i = 0; i < 10000; i++) {
		Rectangle* rect = RectangleRenderer::GetInstance()->addRectangle(glm::vec2(glm::linearRand(-1280.0f*4,1280.0f*4),glm::linearRand(-720.0f*4,720.0f*4)), glm::vec2(glm::linearRand(100.0f,500.0f), glm::linearRand(100.0f,500.0f)), glm::linearRand(0.0f,50.0f), glm::linearRand(0.0f, 50.0f), glm::linearRand(0.0f, 50.0f), glm::linearRand(0.0f, 50.0f), glm::vec3(glm::linearRand(0.0f,1.0f), glm::linearRand(0.0f, 1.0f), glm::linearRand(0.0f, 1.0f)));

		rects.push_back(rect);
	}

	RectangleRenderer::GetInstance()->addRectangle(glm::vec2(0.0f), glm::vec2(400.0f, 200.0f), 5.0f, 5.0f, 5.0f, 5.0f, glm::vec3(1.0f));
	//RectangleRenderer::GetInstance()->addRectangle(glm::vec2(-50.0f,-50.0f), glm::vec2(50.0f, 50.0f), 5.0f, 5.0f, 5.0f, 5.0f, glm::vec3(1.00f));

	//Camera::GetInstance()->setPosition(glm::vec3(640.0f, 360.0f, 0.0f));
	glfwSetKeyCallback(window, Camera::GetInstance()->key_callback);

	

	float t = 0;
	// Main loop
	while (!glfwWindowShouldClose(window))
	{

		//This waits for user input or updates after 1.0 secs
		glfwWaitEventsTimeout(1.0f);
		//glfwPollEvents();

		std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

		//TODO: Not sure if viewport is depecrated or not
		//GLCall(glViewport(0, 0, display_w, display_h));
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

		Camera::GetInstance()->update();

		RectangleRenderer::GetInstance()->render();

		std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::milli> time_span = t2 - t1;
		std::cout << time_span.count() << " ms " << 1000.0f/time_span.count() << " fps " << std::endl;

		//Swap forward and backward buffer
		glfwSwapBuffers(window);

		t += 0.1f;

	}

	RectangleRenderer::GetInstance()->deinit();

	//Cleanup
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
