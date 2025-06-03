#include <Vector2D.h>
#include <vector>
#include <glad/glad.h>
#include <Window.h>
#include <Functions.h>
#include <iostream>
using namespace std;

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

void Vector2D::render(){
	glLineWidth(5.0f); // Ajustá a lo que necesites
	glBindVertexArray(vao);
	glDrawArrays(GL_LINES, 0, vertices.size() / 7);
	glLineWidth(1.0f);
}