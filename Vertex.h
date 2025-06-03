#pragma once
#include <glm/glm.hpp>
#include <vector>
using namespace glm;
using namespace std;

class Vertex {
public:
	vec3 position;
	vec4 color;
	vector<float> floatData;
	Vertex(float x, float y, float r, float g, float b, float t = 1.0f);
	~Vertex();
	void updateFloatData(float dx, float dy);
};