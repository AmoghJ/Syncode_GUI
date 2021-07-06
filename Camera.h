#pragma once

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include <GLFW/glfw3.h>
#include <iostream>

class Camera {
protected:

	static Camera* camera_;

	Camera();

public:
	glm::vec3 position;
	glm::vec3 zoom;
	glm::vec3 center;

	glm::mat4 proj;
	glm::mat4 view;

	glm::mat4 mvp;

	Camera(Camera& other) = delete;
	/**
	 * Singletons should not be assignable.
	 */
	void operator=(const Camera&) = delete;
	/**
	 * This is the static method that controls the access to the singleton
	 * instance. On the first run, it creates a singleton object and places it
	 * into the static field. On subsequent runs, it returns the client existing
	 * object stored in the static field.
	 */

	static Camera* GetInstance();

	void update();

	glm::mat4 getProjectionMatrix();

	glm::mat4 getMVP();
	glm::mat4 getViewMatrix();
	void setPosition(glm::vec3 _p);

	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
};



