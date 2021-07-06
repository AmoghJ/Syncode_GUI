#pragma once

#include "RectangleRenderer.h"
#include "Rectangle.h"

RectangleRenderer* RectangleRenderer::rectangleRenderer_ = nullptr;

RectangleRenderer* RectangleRenderer::GetInstance()
{
	/**
	 * This is a safer way to create an instance. instance = new Singleton is
	 * dangeruous in case two instance threads wants to access at the same time
	 */
	if (rectangleRenderer_ == nullptr) {
		rectangleRenderer_ = new RectangleRenderer();
	}

	return rectangleRenderer_;
}

//Setting up data format based on this approach: https://mortoray.com/2015/06/05/quickly-drawing-a-rounded-rectangle-with-a-gl-shader/

//Mapping - { r0, r1, r2, r3, X, Y, mn, 0, corner0, corner1, corner2, corner3, edge0, edge1, edge2, edge3}


//Defines all vertices needed to render rounded rectangle with linearized parameters

static signed char rectVerts[24 * (6 * 8 + 3 * 8)] = {
	//Corner 0
	0, 0, 0, 0, 0, 0, 0, 0,  // (0,0)
	0, 0, 0, 0, 0, 0, 0, 0,  1, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,  //(0,r0)
	1, 0, 0, 0, 0, 0, 0, 0,  1, 0, 0, 0, 0, 0, 0, 0,
	1, 0, 0, 0, 0, 0, 0, 0,  //(r0,r0)
	1, 0, 0, 0, 0, 0, 0, 0,  1, 0, 0, 0, 0, 0, 0, 0,

	0, 0, 0, 0, 0, 0, 0, 0,  // (0,0)
	0, 0, 0, 0, 0, 0, 0, 0,  1, 0, 0, 0, 0, 0, 0, 0,
	1, 0, 0, 0, 0, 0, 0, 0,  //(r0,r0)
	1, 0, 0, 0, 0, 0, 0, 0,  1, 0, 0, 0, 0, 0, 0, 0,
	1, 0, 0, 0, 0, 0, 0, 0,  // (r0,0)
	0, 0, 0, 0, 0, 0, 0, 0,  1, 0, 0, 0, 0, 0, 0, 0,


	//Corner 1
	0, -1, 0, 0, 1, 0, 0, 0,  //(X-r1,0)
	0, 0, 0, 0, 0, 0, 0, 0,  0, 1, 0, 0, 0, 0, 0, 0,
	0, -1, 0, 0, 1, 0, 0, 0,  //(X-r1,r1)
	0, 1, 0, 0, 0, 0, 0, 0,  0, 1, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 1, 0, 0, 0,  // (X,0) 
	0, 0, 0, 0, 0, 0, 0, 0,  0, 1, 0, 0, 0, 0, 0, 0,

	0, 0, 0, 0, 1, 0, 0, 0,  // (X,0)
	0, 0, 0, 0, 0, 0, 0, 0,  0, 1, 0, 0, 0, 0, 0, 0,
	0, -1, 0, 0, 1, 0, 0, 0,  //(X-r1,r1)
	0, 1, 0, 0, 0, 0, 0, 0,  0, 1, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 1, 0, 0, 0,  //(X,r1)
	0, 1, 0, 0, 0, 0, 0, 0,  0, 1, 0, 0, 0, 0, 0, 0,

	//Corner 2
	0,0,-1,0,1,0,0,0, //(X-r2,Y-r2)
	0,0,-1,0,0,1,0,0, 0, 0, 1, 0, 0, 0, 0, 0,
	0,0,0,0,1,0,0,0, //(X,Y)
	0,0,0,0,0,1,0,0, 0, 0, 1, 0, 0, 0, 0, 0,
	0,0,0,0,1,0,0,0, //(X,Y-r2)
	0,0,-1,0,0,1,0,0, 0, 0, 1, 0, 0, 0, 0, 0,

	0,0,-1,0,1,0,0,0, //(X-r2,Y-r2)
	0,0,-1,0,0,1,0,0, 0, 0, 1, 0, 0, 0, 0, 0,
	0,0,-1,0,1,0,0,0, //(X-r2,Y)
	0,0,0,0,0,1,0,0, 0, 0, 1, 0, 0, 0, 0, 0,
	0,0,0,0,1,0,0,0, //(X,Y)
	0,0,0,0,0,1,0,0, 0, 0, 1, 0, 0, 0, 0, 0,

	//Corner 3
	0,0,0,0,0,0,0,0, //(0,Y-r3)
	0,0,0,-1,0,1,0,0, 0, 0, 0, 1, 0, 0, 0, 0,
	0,0,0,0,0,0,0,0, //(0,Y)
	0,0,0,0,0,1,0,0, 0, 0, 0, 1, 0, 0, 0, 0,
	0,0,0,1,0,0,0,0, //(r3,Y-r3)
	0,0,0,-1,0,1,0,0, 0, 0, 0, 1, 0, 0, 0, 0,

	0,0,0,1,0,0,0,0, //(r3,Y-r3)
	0,0,0,-1,0,1,0,0, 0, 0, 0, 1, 0, 0, 0, 0,
	0,0,0,0,0,0,0,0, //(0,Y)
	0,0,0,0,0,1,0,0, 0, 0, 0, 1, 0, 0, 0, 0,
	0,0,0,1,0,0,0,0, //(r3,Y)
	0,0,0,0,0,1,0,0, 0, 0, 0, 1, 0, 0, 0, 0,

	//Tri 1
	0, 0, 0, 0, 0, 0, 1, 0,  //(mn,mn)
	0, 0, 0, 0, 0, 0, 1, 0,  0, 0, 0, 0, 1, 0, 0, 0,
	1, 0, 0, 0, 0, 0, 0, 0,  // (r0,0)
	0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 1, 0, 0, 0,
	1, 0, 0, 0, 0, 0, 0, 0,  //(r0,r0)
	1, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 1, 0, 0, 0,

	//Tri 2
	0, 0, 0, 0, 0, 0, 1, 0,  //(mn,mn)
	0, 0, 0, 0, 0, 0, 1, 0,  0, 0, 0, 0, 1, 0, 0, 0,
	0, -1, 0, 0, 1, 0, 0, 0, //(X-r1,0)
	0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 1, 0, 0, 0,
	1, 0, 0, 0, 0, 0, 0, 0,  // (r0,0)
	0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 1, 0, 0, 0,

	//Tri 3
	0, 0, 0, 0, 0, 0, 1, 0,  //(mn,mn)
	0, 0, 0, 0, 0, 0, 1, 0,  0, 0, 0, 0, 1, 0, 0, 0,
	0, 0, 0, 0, 1, 0, -1, 0, //(X-mn,mn)
	0, 0, 0, 0, 0, 0, 1, 0,  0, 0, 0, 0, 1, 0, 0, 0,
	0, -1, 0, 0, 1, 0, 0, 0, //(X-r1,0)
	0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 1, 0, 0, 0,

	//Tri 4
	0, 0, 0, 0, 1, 0, -1, 0, //(X-mn,mn)
	0, 0, 0, 0, 0, 0, 1, 0,  0, 0, 0, 0, 1, 0, 0, 0,
	0, -1, 0, 0, 1, 0, 0, 0, //(X-r1,r1)
	0, 1, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 1, 0, 0, 0,
	0, -1, 0, 0, 1, 0, 0, 0, //(X-r1,0)
	0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 1, 0, 0, 0,


	//Tri 5
	0,0,0,0,0,0,1,0, //(mn,Y-mn)
	0,0,0,0,0,1,-1,0, 0, 0, 0, 0, 0, 1, 0, 0,
	0, 0, 0, 1, 0, 0, 0, 0, //(r3,Y-r3)
	0, 0, 0,-1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
	0, 0, 0, 1, 0, 0, 0, 0, //(r3,Y)
	0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,

	//Tri 6
	0, 0, 0, 0, 1, 0, -1, 0,//(X-mn, Y-mn)
	0, 0, 0, 0, 0, 1, -1, 0, 0, 0, 0, 0, 0, 1, 0, 0,
	0, 0, -1, 0, 1, 0, 0, 0, //(X-r2,Y)
	0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
	0, 0, -1, 0, 1, 0, 0, 0, //(X-r2,Y-r2)
	0, 0, -1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,

	//Tri 7
	0, 0, 0, 0, 0, 0, 1, 0, //(mn,Y-mn)
	0, 0, 0, 0, 0, 1, -1, 0, 0, 0, 0, 0, 0, 1, 0, 0,
	0, 0, 0, 1, 0, 0, 0, 0, //(r3,Y)
	0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
	0, 0, 0, 0, 1, 0, -1, 0, //(X-mn, Y-mn)
	0, 0, 0, 0, 0, 1, -1, 0, 0, 0, 0, 0, 0, 1, 0, 0,

	//Tri 8
	0, 0, 0, 0, 1, 0, -1, 0,//(X-mn, Y-mn)
	0, 0, 0, 0, 0, 1, -1, 0, 0, 0, 0, 0, 0, 1, 0, 0,
	0, 0, 0, 1, 0, 0, 0, 0, //(r3,Y)
	0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
	0, 0, -1, 0, 1, 0, 0, 0, //(X-r2,Y)
	0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0,

	//Tri 9
	1, 0, 0, 0, 0, 0, 0, 0, //(r0,r0)
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0,
	0, 0, 0, 0, 0, 0, 0, 0, //(0,r0)
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0,
	0, 0, 0, 0, 0, 0, 1, 0, //(mn,mn)
	0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0,

	//Tri 10
	0, 0, 0, 0, 0, 0, 0, 0, //(0,Y-r3)
	0, 0, 0, -1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0,
	0, 0, 0, 1, 0, 0, 0, 0, //(r3, Y-r3)
	0, 0, 0, -1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0,
	0, 0, 0, 0, 0, 0, 1, 0, //(mn, Y-mn)
	0, 0, 0, 0, 0, 1, -1, 0, 0, 0, 0, 0, 0, 0, 1, 0,

	//Tri 11
	0, 0, 0, 0, 0, 0, 0, 0, //(0,r0)
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0,
	0, 0, 0, 0, 0, 0, 0, 0, //(0,Y-r3)
	0, 0, 0, -1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0,
	0, 0, 0, 0, 0, 0, 1, 0, //(mn,mn)
	0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0,

	//Tri 12
	0, 0, 0, 0, 0, 0, 1, 0, //(mn,mn)
	0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0,
	0, 0, 0, 0, 0, 0, 0, 0, //(0,Y-r3)
	0, 0, 0, -1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0,
	0, 0, 0, 0, 0, 0, 1, 0, //(mn, Y-mn)
	0, 0, 0, 0, 0, 1, -1, 0, 0, 0, 0, 0, 0, 0, 1, 0,

	//Tri 13
	0,-1, 0, 0, 1, 0, 0, 0, //(X-r1,r1)
	0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	0, 0, 0, 0, 1, 0, -1, 0, //(X-mn,mn)
	0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	0, 0, 0, 0, 1, 0, 0, 0, //(X,r1)
	0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,

	//Tri 14
	0, 0, 0, 0, 1, 0, -1, 0, //(X-mn,Y-mn)
	0, 0, 0, 0, 0, 1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	0, 0, -1, 0, 1, 0, 0, 0, //(X-r2,Y-r2)
	0, 0, -1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	0, 0, 0, 0, 1, 0, 0, 0, //(X,Y-r2)
	0, 0, -1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,

	//Tri 15
	0, 0, 0, 0, 1, 0, 0, 0, //(X,r1)
	0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	0, 0, 0, 0, 1, 0, -1, 0, //(X-mn,mn)
	0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	0, 0, 0, 0, 1, 0, -1, 0, //(X-mn,Y-mn)
	0, 0, 0, 0, 0, 1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 1,

	//Tri 16
	0, 0, 0, 0, 1, 0, 0, 0, //(X,r1)
	0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	0, 0, 0, 0, 1, 0, -1, 0, //(X-mn,Y-mn)
	0, 0, 0, 0, 0, 1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	0, 0, 0, 0, 1, 0, 0, 0, //(X,Y-r2)
	0, 0, -1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,

};



RectangleRenderer::RectangleRenderer() {

	createRectangleShader();

	//Generate VAO and VBO and bind attrib pointers
	GLCall(glGenVertexArrays(1, &vertexArrayObject));
	GLCall(glBindVertexArray(vertexArrayObject));

	GLCall(glGenBuffers(1, &vertexBuffer));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer));
	GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(signed char) * 24 * (6 * 8 + 3 * 8), &rectVerts[0], GL_STATIC_DRAW));

	GLCall(glEnableVertexAttribArray(0));
	GLCall(glEnableVertexAttribArray(1));
	GLCall(glEnableVertexAttribArray(2));
	GLCall(glEnableVertexAttribArray(3));
	GLCall(glEnableVertexAttribArray(4));
	GLCall(glEnableVertexAttribArray(5));

	//For X
	// 0, 0, 0, 0, - Defines r0, r1, r2,r3
	GLCall(glVertexAttribPointer(0, 4, GL_BYTE, GL_FALSE, sizeof(signed char) * 24, 0));
	// 0, 0, 0, 0, - Defines X, Y, mn, 0
	GLCall(glVertexAttribPointer(1, 4, GL_BYTE, GL_FALSE, sizeof(signed char) * 24, (GLvoid*)(sizeof(signed char) * 4)));

	//For Y
	// 0, 0, 0, 0, - Defines r0, r1, r2,r3
	GLCall(glVertexAttribPointer(2, 4, GL_BYTE, GL_FALSE, sizeof(signed char) * 24, (GLvoid*)(sizeof(signed char) * 8)));
	// 0, 0, 0, 0, - Defines X, Y, mn, 0
	GLCall(glVertexAttribPointer(3, 4, GL_BYTE, GL_FALSE, sizeof(signed char) * 24, (GLvoid*)(sizeof(signed char) * 12)));

	//At end
	// 0, 0, 0, 0, - Defines radius 0, 1, 2, 3
	GLCall(glVertexAttribPointer(4, 4, GL_BYTE, GL_FALSE, sizeof(signed char) * 24, (GLvoid*)(sizeof(signed char) * 16)));
	// 0, 0, 0, 0, - Defines edge 0, 1, 2, 3
	GLCall(glVertexAttribPointer(5, 4, GL_BYTE, GL_FALSE, sizeof(signed char) * 24, (GLvoid*)(sizeof(signed char) * 20)));

	glGenBuffers(1, &rectBuffer);

}


void RectangleRenderer::render() {

	//Checks to see if rectangle has update flag
	for (int i = 0; i < rectangles.size(); i++) {
		if (rectangles.at(i)->update)
			updateRectangle(rectangles.at(i));
	}

	GLCall(glBindVertexArray(vertexArrayObject));
	GLCall(glUseProgram(getRectangleShader()));

	GLCall(int mvp = glGetUniformLocation(getRectangleShader(), "u_MVP"));
	ASSERT(mvp != -1);
	GLCall(glUniformMatrix4fv(mvp, 1, GL_FALSE, &Camera::GetInstance()->getMVP()[0][0]));

	GLCall(int mv = glGetUniformLocation(getRectangleShader(), "u_MV"));
	ASSERT(mv != -1);
	GLCall(glUniformMatrix4fv(mv, 1, GL_FALSE, &Camera::GetInstance()->getViewMatrix()[0][0]));

	//GLCall(glDrawElements(GL_TRIANGLES, 8 * 3, GL_UNSIGNED_INT, nullptr));
	//GLCall(glDrawArrays(GL_TRIANGLES, 0, 24 * (6 * 8 + 3*8)));
	glDrawArraysInstanced(GL_TRIANGLES, 0, 72, rectangles.size());
}

//TODO: Add functionality to remove rectangle
//TODO: Sort rectangle order

Rectangle* RectangleRenderer::addRectangle(glm::vec2 pos, glm::vec2 size, float r1, float r2, float r3, float r4, glm::vec3 color) {

	Rectangle* rect = new Rectangle(pos, size, r1, r2, r3, r4, color);
	rect->index = rectangles.size();

	rectangles.push_back(rect);

	for (int i = rect->index; i < rectangles.size(); i++) {
		rectData.push_back(rectangles[i]->pos.x);
		rectData.push_back(rectangles[i]->pos.y);
		rectData.push_back(rectangles[i]->size.x);
		rectData.push_back(rectangles[i]->size.y);
		rectData.push_back(rectangles[i]->r0);
		rectData.push_back(rectangles[i]->r1);
		rectData.push_back(rectangles[i]->r2);
		rectData.push_back(rectangles[i]->r3);
		rectData.push_back(rectangles[i]->color.r);
		rectData.push_back(rectangles[i]->color.g);
		rectData.push_back(rectangles[i]->color.b);
	}

	glBindVertexArray(vertexArrayObject);

	glBindBuffer(GL_ARRAY_BUFFER, rectBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * rectData.size(), rectData.data(), GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(6);
	glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 11, 0);
	glVertexAttribDivisor(6, 1);

	glEnableVertexAttribArray(7);
	glVertexAttribPointer(7, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 11, (GLvoid*)(sizeof(float) * 4));
	glVertexAttribDivisor(7, 1);

	glEnableVertexAttribArray(8);
	glVertexAttribPointer(8, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 11, (GLvoid*)(sizeof(float) * 8));
	glVertexAttribDivisor(8, 1);

	return rect;
}

void RectangleRenderer::deinit() {
	deleteRectangleShader();
}

unsigned int RectangleRenderer::getRectangleShader() {
	return RectangleShader;
}

void RectangleRenderer::createRectangleShader() {
	ShaderProgramSource source = ParseShader("res/shaders/Rectangle.shader");

	unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);

	RectangleShader = shader;
}

void RectangleRenderer::deleteRectangleShader() {
	GLCall(glDeleteProgram(getRectangleShader()));
}

void RectangleRenderer::updateRectangle(Rectangle* rectangle) {
	int index = rectangle->index;

	rectangles[index]->pos = rectangle->pos;
	rectangles[index]->size = rectangle->size;
	rectangles[index]->r0 = rectangle->r0;
	rectangles[index]->r1 = rectangle->r1;
	rectangles[index]->r2 = rectangle->r2;
	rectangles[index]->r3 = rectangle->r3;
	rectangles[index]->color = rectangle->color;

	rectData[index * 11 + 0] = rectangle->pos.x;
	rectData[index * 11 + 1] = rectangle->pos.y;
	rectData[index * 11 + 2] = rectangle->size.x;
	rectData[index * 11 + 3] = rectangle->size.y;
	rectData[index * 11 + 4] = rectangle->r0;
	rectData[index * 11 + 5] = rectangle->r1;
	rectData[index * 11 + 6] = rectangle->r2;
	rectData[index * 11 + 7] = rectangle->r3;
	rectData[index * 11 + 8] = rectangle->color.r;
	rectData[index * 11 + 9] = rectangle->color.g;
	rectData[index * 11 + 10] = rectangle->color.b;

	glBindVertexArray(vertexArrayObject);
	glBindBuffer(GL_ARRAY_BUFFER,rectBuffer);
	GLCall(glBufferSubData(GL_ARRAY_BUFFER, index * sizeof(float) * 11, sizeof(float) * 11, rectData.data()));

	rectangle->update = false;
}