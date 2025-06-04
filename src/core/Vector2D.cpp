#include <Vector2D.h>
#include <vector>
#include <glad/glad.h>
#include <Window.h>
#include <Functions.h>
#include <iostream>
#include <glm/glm.hpp>
using namespace std;
using namespace glm;
void Vector2D::getArrow() {
	float angleDegrees = 30.0f;
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

	vertices.insert(vertices.end(), {
		endX, endY, 0.0f, r, g, b, a,
		x1, y1, 0.0f, r, g, b, a,
		endX, endY, 0.0f, r, g, b, a,
		x2, y2, 0.0f, r, g, b, a
		});
}



void Vector2D::generateVaoAndVbo() {
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1,&vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_DYNAMIC_DRAW);

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

	cout << a << endl;
	window = w;
	updateVertices();
	generateVaoAndVbo();
}

Vector2D::Vector2D(float magnitude, float direction, float r, float g, float b, float a, Window* w) : magnitude(magnitude), direction(direction) {
	this->r = rgbToGL(r);
	this->g = rgbToGL(g);
	this->b = rgbToGL(b);

	this->a = a;

	cout << a << endl;
	window = w;
	updateVertices();
	generateVaoAndVbo();
}


Vector2D::Vector2D(float magnitude, float direction, float startX, float startY, float r, float g, float b, Window* w) : magnitude(magnitude), direction(direction), startX(startX), startY(startY) {
	this->r = rgbToGL(r);
	this->g = rgbToGL(g);
	this->b = rgbToGL(b);
	this->a = 1.0f;
	window = w;
	updateVertices();
	generateVaoAndVbo();
}

Vector2D::~Vector2D(){}



void Vector2D::updateVertices() {
	vertices = vector<float>({
			startX, startY, 0.0f, r,g,b, a,
		});

	float convertedMagnitudeX = pixelMagnitudeToGL(magnitude, window->width);
	float convertedMagnitudeY = pixelMagnitudeToGL(magnitude, window->height);
	float convertedAngle = degreesToRads(direction);


	float endPointX = startX + cos(convertedAngle) * convertedMagnitudeX;
	float endPointY = startY + sin(convertedAngle) * convertedMagnitudeY;

	vertices.insert(vertices.end(), {
			endPointX, endPointY, 0.0f, r, g, b ,a
		});

	endX = endPointX;
	endY = endPointY;
	getArrow();

	glBindBuffer(GL_ARRAY_BUFFER,vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(float), vertices.data() );
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Vector2D::render() {
	glLineWidth(3.0f); 
	glBindVertexArray(vao);
	glDrawArrays(GL_LINES, 0, vertices.size() / 7);
	glLineWidth(1.0f);
}

void Vector2D::setMagnitude(float newM) {
	magnitude = newM;
	updateVertices();
}

void Vector2D::rotate(float degrees) {
	direction += degreesToRads(degrees);
	updateVertices();
}

vec2 Vector2D::getComponents() {
	vec2 components;
	components.x = /*pixelsToGL(startX, window->width) +*/ cos(degreesToRads(direction)) * pixelMagnitudeToGL(magnitude, window->width);
	components.y = /*pixelsToGL(startY, window->height) +*/ sin(degreesToRads(direction)) * pixelMagnitudeToGL(magnitude, window->height);
	return components;
}

