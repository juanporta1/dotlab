#pragma once
#include <vector>
#include <Vertex.h>
#include <Window.h>
using namespace std;

class Ball {
public:
	GLuint vao, vbo;
	vector<Vertex*> vertices;
	Window* window;
	Vertex* center;
	vector<float> floatVerticesData;
	float velX = 0.0f;
	float velY = 0.0f;
	float accX = 0.0f;
	float accY = 0.0f;
	Ball(float x, float y, float radius, float r, float g, float b, Window* window);
	~Ball();

	void updateFloatVerticesData();
	void updateVertices(float dt);
	void updateBuffer();
	void render();
	void update(float deltaTime);
};