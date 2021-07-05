#pragma once

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"

#include <iostream>

class Camera {
protected:

	static Camera* camera_;

	Camera() {
		position = glm::vec3(0.0f);
		zoom = glm::vec3(1.0f);

		//Setup projection matrix with 16:9 aspect ratio
		//TODO: Make dynamic screen size
		proj = glm::ortho(0.0f, 1280.0f, 720.0f, 0.0f, -1.0f, 1.0f);
		view = glm::scale(glm::translate(glm::mat4(1.0f), position),zoom);
		mvp = proj*view;
	}

public:
	glm::vec3 position;
	glm::vec3 zoom;

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

	void update() {
		view = glm::scale(glm::translate(glm::mat4(1.0f), position),zoom);
		mvp = proj * view;
	}

	glm::mat4 getProjectionMatrix() {
		return proj;
	}

	glm::mat4 getMVP() {
		return mvp;
	}

	glm::mat4 getViewMatrix() {
		return view;
	}

	void setPosition(glm::vec3 _p) {
		position = _p;
	}

	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
};

Camera* Camera::camera_ = nullptr;

Camera* Camera::GetInstance()
{
	/**
	 * This is a safer way to create an instance. instance = new Singleton is
	 * dangeruous in case two instance threads wants to access at the same time
	 */
	if (camera_ == nullptr) {
		camera_ = new Camera();
	}
	return camera_;
}

void Camera::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {

	if (key == GLFW_KEY_W) {
		GetInstance()->position.y -= 3.0f;
	}

	if (key == GLFW_KEY_S) {
		GetInstance()->position.y += 3.0f;
	}

	if (key == GLFW_KEY_A) {
		GetInstance()->position.x -= 3.0f;
	}

	if (key == GLFW_KEY_D) {
		GetInstance()->position.x += 3.0f;
	}

	if (key == GLFW_KEY_Q) {
		GetInstance()->zoom += glm::vec3(0.1f);
	}

	if (key == GLFW_KEY_E) {
		GetInstance()->zoom -= glm::vec3(0.1f);
	}

	std::cout << GetInstance()->getViewMatrix()[0][0] << " " << GetInstance()->getViewMatrix()[1][1] << std::endl;
}