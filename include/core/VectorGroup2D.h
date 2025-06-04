#pragma once
#include <Vector2D.h>
#include <Window.h>
#include <vector>
using namespace std;
class VectorGroup2D {
public:
	vector<Vector2D> vectors;
	Window* window;
	Vector2D mainVector;

	VectorGroup2D(vector<Vector2D> vectors, Window* window);
	~VectorGroup2D();

	void addVector(Vector2D vec);
	void getSum();
	void render();
};