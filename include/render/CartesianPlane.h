#pragma once
#include <glad/glad.h>
#include <vector>
#include <Window.h>
using namespace std;
class CartesianPlane {
public:
	float x = 0.0f;
	float y = 0.0f;
	GLuint vao, vbo;
	Window* window;
	vector<float> vertices;
	CartesianPlane(Window* w);
	~CartesianPlane();
	void render();
};