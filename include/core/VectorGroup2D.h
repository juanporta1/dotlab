#pragma once
#include <Vector2D.h>
#include <Window.h>
#include <vector>

struct VectorGroupOptions {
	bool renderComponents = true;
};

using namespace std;
class VectorGroup2D {	
public:
	
	vector<Vector2D> vectors;
	Window* window;
	Vector2D mainVector = Vector2D(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, window);
	VectorGroupOptions options;
	Vector2D xComponent = Vector2D(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, window), yComponent = Vector2D(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, window);

	VectorGroup2D(vector<Vector2D> vectors, Window* window, VectorGroupOptions options);
	~VectorGroup2D();

	void addVector(Vector2D vec);
	void getSum();
	void render();
};