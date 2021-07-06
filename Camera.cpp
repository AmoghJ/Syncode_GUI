#pragma once

#include "Camera.h"

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

Camera::Camera() {
	position = glm::vec3(0.0f);
	zoom = glm::vec3(1.0f);

	//Setup projection matrix with 16:9 aspect ratio
	//TODO: Make dynamic screen size
	proj = glm::ortho(0.0f, 1280.0f, 720.0f, 0.0f, -1.0f, 1.0f);

	center = glm::vec3(640.0f, 360.0f,0.0f);

	view = glm::translate(glm::mat4(1.0f), -position) * glm::translate(glm::mat4(1.0f), center) * glm::scale(glm::mat4(1.0f), zoom) * glm::translate(glm::mat4(1.0f), -center);
	mvp = proj * view;
}

void Camera::update() {
	view = glm::translate(glm::mat4(1.0f), -position) * glm::translate(glm::mat4(1.0f), center) * glm::scale(glm::mat4(1.0f),zoom) * glm::translate(glm::mat4(1.0f), -center);
	
	mvp = proj * view;
}

glm::mat4 Camera::getProjectionMatrix() {
	return proj;
}

glm::mat4 Camera::getMVP() {
	return mvp;
}

glm::mat4 Camera::getViewMatrix() {
	return view;
}

void Camera::setPosition(glm::vec3 _p) {
	position = _p;
}

void Camera::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {

	if (key == GLFW_KEY_W) {
		GetInstance()->position.y -= 3.0f/GetInstance()->zoom.x;
	}

	if (key == GLFW_KEY_S) {
		GetInstance()->position.y += 3.0f/GetInstance()->zoom.x;
	}

	if (key == GLFW_KEY_A) {
		GetInstance()->position.x -= 3.0f/ GetInstance()->zoom.x;
	}

	if (key == GLFW_KEY_D) {
		GetInstance()->position.x += 3.0f/ GetInstance()->zoom.x;
	}

	if (key == GLFW_KEY_Q) {
		GetInstance()->zoom += glm::vec3(0.1f)*GetInstance()->zoom.x;
	}

	if (key == GLFW_KEY_E) {
		GetInstance()->zoom -= glm::vec3(0.1f) * GetInstance()->zoom.x;
	}
}