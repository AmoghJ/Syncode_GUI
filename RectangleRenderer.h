#pragma once

#include <GL/glew.h>

#include <vector>
#include <iostream>

#include "Shaders.h"
#include "Error.h"
#include "Camera.h"

class Rectangle;

class RectangleRenderer {
protected:
	static RectangleRenderer* rectangleRenderer_;

	RectangleRenderer();

public:
	unsigned int vertexArrayObject;
	unsigned int vertexBuffer;
	unsigned int rectBuffer;

	//Have one global rectangle shader
	unsigned int RectangleShader;

	std::vector<Rectangle*> rectangles;
	std::vector<float> rectData;
	int currentBufferSize = 0;

	RectangleRenderer(RectangleRenderer& other) = delete;
	/**
	 * Singletons should not be assignable.
	 */
	void operator=(const RectangleRenderer&) = delete;
	/**
	 * This is the static method that controls the access to the singleton
	 * instance. On the first run, it creates a singleton object and places it
	 * into the static field. On subsequent runs, it returns the client existing
	 * object stored in the static field.
	 */

	static RectangleRenderer* GetInstance();

	void render();
	void deinit();

	Rectangle* addRectangle(glm::vec2 pos, glm::vec2 size, float r1, float r2, float r3, float r4, glm::vec3 color);

	unsigned int getRectangleShader();

	//Call once in setup
	void createRectangleShader();

	//Call at end for cleanup
	void deleteRectangleShader();

	void updateRectangle(Rectangle* rect);
};

