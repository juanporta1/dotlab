#pragma once
#include <vector>
#include <Vertex.h>
#include <Window.h>
#include <VectorGroup2D.h>
using namespace std;

class Ball {
private:
	
	void calculateBound(float dt);
	void recalculateVertices();
public:
	GLuint vao, vbo;
	vector<Vertex> vertices;
	Window* window;
	vector<float> floatVerticesData;
	float velX = 0.0f;
	float velY = 0.0f;
	float accX = 0.0f;
	float accY = 0.0f;
	float mass = 0.0f;
	float radius;
	float kConstant = 100.0f;
	VectorGroup2D forces;
	vector<Vector2D> vectors;
	Vector2D gravityVector;
	Vector2D reboundVector;

	Ball(float x, float y, float radius, float r, float g, float b, Window* window);
	~Ball();

	void updateFloatVerticesData();
	void updateVertices(float dt);
	void updateBuffer();
	void render();
	void update(float deltaTime);
};