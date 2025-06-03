#include <Ball.h>
#include <Functions.h>
#include <vector>
#include <Vertex.h>
#include <iostream>
using namespace std;



Ball::Ball(float x, float y, float radius, float r, float g, float b, Window* window) : window(window)
{
	float glFirstX = pixelsToGL(x, window->width);
	float glFirstY = pixelsToGL(y, window->height);
	float glR = rgbToGL(r);
	float glG = rgbToGL(g);
	float glB = rgbToGL(b);
	Vertex vertex(glFirstX, glFirstY, glR, glG, glB);
	vertices = vector<Vertex>({ vertex });
	center = &vertices[0];
	for (int i = 0; i < 37; i++) {
		float angle = 2.0f * 3.14159265359 * i / 36;
		float pX = x + cos(angle) * radius;
		float pY = y + sin(angle) * radius;

		float glX = pixelsToGL(pX, window->width);
		float glY = pixelsToGL(pY, window->height);
		Vertex v(glX, glY, glR, glG, glB, 1.0f);
		vertices.push_back(v);
	}

	updateFloatVerticesData();

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, floatVerticesData.size() * sizeof(float), floatVerticesData.data(), GL_DYNAMIC_DRAW);

	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//Color
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
Ball::~Ball(){}

void Ball::render() {
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLE_FAN, 0, static_cast<GLsizei>(vertices.size()));
}

void Ball::update(float dt) {

	velX += accX * dt;
	velY += accY * dt;

	updateVertices(dt);
	updateFloatVerticesData();
	updateBuffer();
}

void Ball::updateVertices(float dt) {
	float deltaX = velX * dt + 0.5f * accX * dt * dt;
	float deltaY = velY * dt + 0.5f * accY * dt * dt;
	for (Vertex& v : vertices) {
		v.updateFloatData(deltaX, deltaY);
	}
}

void Ball::updateFloatVerticesData() {
	floatVerticesData.clear();
	for (Vertex& v : vertices) {
		floatVerticesData.push_back(v.position.x);
		floatVerticesData.push_back(v.position.y);
		floatVerticesData.push_back(v.position.z);
		floatVerticesData.push_back(v.color.r);
		floatVerticesData.push_back(v.color.g);
		floatVerticesData.push_back(v.color.b);
		floatVerticesData.push_back(v.color.a);
	}
}

void Ball::updateBuffer() {
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, floatVerticesData.size() * sizeof(float), floatVerticesData.data());
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}