#pragma once
#include <glm/glm.hpp>
#include <vector>
using namespace glm;
using namespace std;

class Vertex {
public:
	vec3 position;
	vec3 color;
	vector<float> floatData;
	Vertex(float x, float y, float r, float g, float b);
	~Vertex();
	void updateFloatData(float dx, float dy);
};