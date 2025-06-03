#pragma once
#include <vector>
#include <glad/glad.h>
#include <Window.h>
using namespace std;

class Vector2D {
private:
	void generateVaoAndVbo();

public:
	float magnitude, direction;
	float startX = 0.0f, startY = 0.0f;
	float r, b, g, a;
	Window* window;
	GLuint vao, vbo;
	vector<float> vertices;
	Vector2D(float magnitude, float direction, float r, float g, float b, Window* w);
	Vector2D(float magnitude, float direction, float startX, float startY, float r, float g, float b, Window* w);
	~Vector2D();
	void updateVertices();
	void render();
};