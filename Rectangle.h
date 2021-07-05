#pragma once

#include <GL/glew.h>

#include <vector>
#include <iostream>

#include "Shaders.h"
#include "Error.h"
#include "Camera.h"


//Setting up data format based on this approach: https://mortoray.com/2015/06/05/quickly-drawing-a-rounded-rectangle-with-a-gl-shader/

//Mapping - { r0, r1, r2, r3, X, Y, mn, 0, corner0, corner1, corner2, corner3, edge0, edge1, edge2, edge3}


//Defines all vertices needed to render rounded rectangle with linearized parameters

static signed short rectVerts[24*(6*8 + 3*8)] = {
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


//Have on global rectangle shader
unsigned int RectangleShader;
unsigned int getRectangleShader() {
	return RectangleShader;
}

//Call once in setup
void createRectangleShader() {
	ShaderProgramSource source = ParseShader("res/shaders/Rectangle.shader");

	unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);

	RectangleShader = shader;
}

//Call at end for cleanup
void deleteRectangleShader() {
	GLCall(glDeleteProgram(getRectangleShader()));
}

class Rectangle {
public:
	//Specifies X and Y
	float sizeX, sizeY;

	//Specifies radius for each corner
	float r0, r1, r2, r3;

	//min(X,Y)/2
	float mn;

	unsigned int vertexArrayObject;

	Rectangle() {


		//Generate VAO and VBO and bind attrib pointers
		unsigned int vao;
		GLCall(glGenVertexArrays(1, &vao));
		GLCall(glBindVertexArray(vao));

		vertexArrayObject = vao;

		unsigned int vertexBuffer;
		GLCall(glGenBuffers(1, &vertexBuffer));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer));
		GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(signed short) * 24 * (6 * 8 + 3*8), &rectVerts[0], GL_STATIC_DRAW));

		GLCall(glEnableVertexAttribArray(0));
		GLCall(glEnableVertexAttribArray(1));
		GLCall(glEnableVertexAttribArray(2));
		GLCall(glEnableVertexAttribArray(3));
		GLCall(glEnableVertexAttribArray(4));
		GLCall(glEnableVertexAttribArray(5));

		//For X
		// 0, 0, 0, 0, - Defines r0, r1, r2,r3
		GLCall(glVertexAttribPointer(0, 4, GL_SHORT, GL_FALSE, sizeof(signed short) * 24, 0));
		// 0, 0, 0, 0, - Defines X, Y, mn, 0
		GLCall(glVertexAttribPointer(1, 4, GL_SHORT, GL_FALSE, sizeof(signed short) * 24, (GLvoid*)(sizeof(signed short)*4)));
		
		//For Y
		// 0, 0, 0, 0, - Defines r0, r1, r2,r3
		GLCall(glVertexAttribPointer(2, 4, GL_SHORT, GL_FALSE, sizeof(signed short) * 24, (GLvoid*)(sizeof(signed short) * 8)));
		// 0, 0, 0, 0, - Defines X, Y, mn, 0
		GLCall(glVertexAttribPointer(3, 4, GL_SHORT, GL_FALSE, sizeof(signed short) * 24, (GLvoid*)(sizeof(signed short) * 12)));
		
		//At end
		// 0, 0, 0, 0, - Defines radius 0, 1, 2, 3
		GLCall(glVertexAttribPointer(4, 4, GL_SHORT, GL_FALSE, sizeof(signed short) * 24, (GLvoid*)(sizeof(signed short) * 16)));
		// 0, 0, 0, 0, - Defines edge 0, 1, 2, 3
		GLCall(glVertexAttribPointer(5, 4, GL_SHORT, GL_FALSE, sizeof(signed short) * 24, (GLvoid*)(sizeof(signed short) * 20)));
	}

	void render() {

		GLCall(glBindVertexArray(vertexArrayObject));

		GLCall(glUseProgram(getRectangleShader()));

		GLCall(int mvp = glGetUniformLocation(getRectangleShader(), "u_MVP"));
		ASSERT(mvp != -1);
		GLCall(glUniformMatrix4fv(mvp, 1, GL_FALSE, &Camera::GetInstance()->getMVP()[0][0]));

		GLCall(int mv = glGetUniformLocation(getRectangleShader(), "u_MV"));
		ASSERT(mv != -1);
		GLCall(glUniformMatrix4fv(mv, 1, GL_FALSE, &Camera::GetInstance()->getViewMatrix()[0][0]));

		GLCall(int cR = glGetUniformLocation(getRectangleShader(), "cR"));
		ASSERT(cR != -1);
		GLCall(glUniform4f(cR, 50.0f, 20.0f, 10.0f, 0.0f));

		GLCall(int s = glGetUniformLocation(getRectangleShader(), "s"));
		ASSERT(s != -1);
		GLCall(glUniform2f(s, 200.0f, 200.0f));

		GLCall(int mn = glGetUniformLocation(getRectangleShader(), "mn"));
		ASSERT(mn != -1);
		glUniform1f(mn, glm::min(200.0f, 200.0f) / 2.0f);

		//GLCall(glDrawElements(GL_TRIANGLES, 8 * 3, GL_UNSIGNED_INT, nullptr));
		GLCall(glDrawArrays(GL_TRIANGLES, 0, 24 * (6 * 8 + 3*8)));
	}
};