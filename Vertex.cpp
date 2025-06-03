#include <Vertex.h>
#include <glm/glm.hpp>
using namespace glm;
Vertex::Vertex(float x, float y, float r, float g, float b) {
	position = vec3(x, y, 0.0f);
	color = vec3(r, g, b);
}

Vertex::~Vertex(){}

void Vertex::updateFloatData(float dx, float dy) {
	position.x += dx;
	position.y += dy;
	floatData.clear();
	floatData.push_back(position.x);
	floatData.push_back(position.y);
	floatData.push_back(position.z);
	floatData.push_back(color.r);
	floatData.push_back(color.g);
	floatData.push_back(color.b);
}
