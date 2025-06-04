#pragma once
#include <vector>
#include <glad/glad.h>
#include <Window.h>
#include <glm/glm.hpp>
using namespace std;
using namespace glm;
class Vector2D {
private:
	void generateVaoAndVbo();
	void getArrow();
public:
	float magnitude, direction;
	float startX = 0.0f, startY = 0.0f;
	float endX = 0.0f, endY = 0.0f;
	float r, b, g, a;
	Window* window;
	GLuint vao, vbo;
	vector<float> vertices;
	Vector2D(float magnitude, float direction, float r, float g, float b, Window* w);
	Vector2D(float magnitude, float direction, float r, float g, float b, float a , Window* w);
	Vector2D(float magnitude, float direction, float startX, float startY, float r, float g, float b, Window* w);
	~Vector2D();

	void updateVertices();
	void render();
	void setMagnitude(float newMagnitude);
	void rotate(float degrees);
	vec2 getComponents();
};