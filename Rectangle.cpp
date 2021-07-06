#pragma once

#include "Rectangle.h"
#include "RectangleRenderer.h"

Rectangle::Rectangle(glm::vec2 pos_, glm::vec2 size_, float r0_, float r1_, float r2_, float r3_, glm::vec3 color_) {
	pos = pos_;
	size = size_;
	r0 = r0_;
	r1 = r1_;
	r2 = r2_;
	r3 = r3_;
	color = color_;
}

void Rectangle::setColor(glm::vec3 color_) {
	color = color_;

	update = true;
}

void Rectangle::setPosition(glm::vec2 pos_) {
	pos = pos_;

	update = true;
}