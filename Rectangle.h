#pragma once

#include "glm.hpp"

class RectangleRenderer;

class Rectangle {

	friend class RectangleRenderer;

private:
	int index;
	Rectangle(glm::vec2 pos_, glm::vec2 size_, float r0_, float r1_, float r2_, float r3_, glm::vec3 color_);

	glm::vec2 pos;
	glm::vec2 size;
	float r0, r1, r2, r3;
	glm::vec3 color;

	bool update = false;

public:
	void setColor(glm::vec3 color_);
	void setPosition(glm::vec2 pos_);
};