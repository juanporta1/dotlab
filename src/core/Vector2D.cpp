#include <Vector2D.h>
#include <vector>
#include <glad/glad.h>
#include <Window.h>
#include <Functions.h>
#include <iostream>
#include <glm/glm.hpp>
using namespace std;
using namespace glm;


void Vector2D::generateVaoAndVbo() {
	glGenVertexArrays(1, &vao);
	glGenVertexArrays(1, &arrowVao);
	

	glGenBuffers(1,&vbo);
	glGenBuffers(1, &arrowVbo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_DYNAMIC_DRAW);

	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//Color
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, arrowVbo);
	glBindVertexArray(arrowVao);

	glBufferData(GL_ARRAY_BUFFER, arrowVertices.size() * sizeof(float), arrowVertices.data(), GL_DYNAMIC_DRAW);

	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//Color
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}



Vector2D::Vector2D(float magnitude, float direction, float r, float g, float b, Window* w) : magnitude(magnitude), direction(direction) {
	this->r = rgbToGL(r);
	this->g = rgbToGL(g);
	this->b = rgbToGL(b);

	this->a = 1.0f;

	window = w;
	startX = window->width / 2;
	startY = window->height / 2;
	updateVertices();
	generateVaoAndVbo();
}

Vector2D::Vector2D(float magnitude, float direction, float r, float g, float b, float a, Window* w) : magnitude(magnitude), direction(direction) {
	this->r = rgbToGL(r);
	this->g = rgbToGL(g);
	this->b = rgbToGL(b);

	this->a = a;

	window = w;
	startX = window->width / 2;
	startY = window->height / 2;

	updateVertices();
	generateVaoAndVbo();
}


Vector2D::Vector2D(float magnitude, float direction, float sX, float sY, float r, float g, float b, Window* w) : magnitude(magnitude), direction(direction), window(w) {
	this->r = rgbToGL(r);
	this->g = rgbToGL(g);
	this->b = rgbToGL(b);

	this->a = 1.0f;

	startX = sX;
	startY = sY;
	updateVertices();
	generateVaoAndVbo();
}

Vector2D::~Vector2D(){}

void Vector2D::getArrow() {
	float angleDegrees = 25.0f;
	float size = 15.0f;
	float sizeX = pixelMagnitudeToGL(size, window->width);
	float sizeY = pixelMagnitudeToGL(size, window->height);

	float angle1 = (direction + 180.0f) - angleDegrees;
	float angle2 = (direction + 180.0f) + angleDegrees;

	float convertedAngle1 = degreesToRads(angle1);
	float convertedAngle2 = degreesToRads(angle2);

	float x1 = endX + cos(convertedAngle1) * sizeX;
	float y1 = endY + sin(convertedAngle1) * sizeY;
	float x2 = endX + cos(convertedAngle2) * sizeX;
	float y2 = endY + sin(convertedAngle2) * sizeY;

	arrowVertices.insert(arrowVertices.end(), {
		endX, endY, 0.0f, r, g, b, a,
		x1, y1, 0.0f, r, g, b, a,
		x2, y2, 0.0f, r, g, b, a
		});
}



void Vector2D::updateVertices() {
	vertices.clear();
	arrowVertices.clear();

	float bodyWidthX = pixelMagnitudeToGL(2.0f, window->width);
	float bodyWidthY = pixelMagnitudeToGL(2.0f, window->height);

	float magnitudeGL_X = pixelMagnitudeToGL(magnitude, window->width);
	float magnitudeGL_Y = pixelMagnitudeToGL(magnitude, window->height);

	float angleRadians = degreesToRads(direction);

	float unitX = cos(angleRadians);
	float unitY = sin(angleRadians);

	float convertedStartX = pixelsToGL(startX,window->width);
	float convertedStartY = pixelsToGL(startY,window->height);

	float baseLeftX = convertedStartX + -unitY * bodyWidthX;
	float baseLeftY = convertedStartY +  unitX * bodyWidthY;
	float baseRightX = convertedStartX + unitY * bodyWidthX;
	float baseRightY = convertedStartY + -unitX * bodyWidthY;

	float finalTipX = convertedStartX + unitX * magnitudeGL_X;
	float finalTipY = convertedStartY + unitY * magnitudeGL_Y;

	float bodyEndX = convertedStartX + unitX * (magnitudeGL_X - pixelMagnitudeToGL(5.0f, window->width));
	float bodyEndY = convertedStartY + unitY * (magnitudeGL_Y - pixelMagnitudeToGL(5.0f, window->height));

	float endLeftX = bodyEndX + -unitY * bodyWidthX;
	float endLeftY =  bodyEndY + unitX * bodyWidthY;
	float endRightX =  bodyEndX + unitY * bodyWidthX;
	float endRightY = bodyEndY + -unitX * bodyWidthY;

	vertices.insert(vertices.end(), {
		// Triángulo 1
		baseLeftX, baseLeftY, 0.0f, r, g, b, a,
		baseRightX, baseRightY, 0.0f, r, g, b, a,
		endLeftX, endLeftY, 0.0f, r, g, b, a,
		// Triángulo 2
		baseRightX, baseRightY, 0.0f, r, g, b, a,
		endLeftX, endLeftY, 0.0f, r, g, b, a,
		endRightX, endRightY, 0.0f, r, g, b, a
		});

	endX = finalTipX;
	endY = finalTipY;

	getArrow();

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(float), vertices.data());

	glBindBuffer(GL_ARRAY_BUFFER, arrowVbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, arrowVertices.size() * sizeof(float), arrowVertices.data());

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


void Vector2D::render() {
	if (magnitude == 0.0f) return;
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 7);
	glBindVertexArray(arrowVao);
	glDrawArrays(GL_TRIANGLES, 0, arrowVertices.size() / 7);
	glBindVertexArray(0);
}

void Vector2D::setMagnitude(float newM) {
	magnitude = newM;
	updateVertices();
}

void Vector2D::rotate(float degrees) {
	direction += degrees;
	updateVertices();
}

void Vector2D::setDirection(float degrees) {
	direction = degrees;
	updateVertices();
}

vec2 Vector2D::getComponents() {
	vec2 components;
	components.x =  cos(degreesToRads(direction)) * pixelMagnitudeToGL(magnitude, window->width);
	components.y = sin(degreesToRads(direction)) * pixelMagnitudeToGL(magnitude, window->height);
	return components;
}


void Vector2D::move(float x, float y) {
	startX = x;
	startY = y;
	updateVertices();
}
