#include <CartesianPlane.h>
#include <vector>
#include <Window.h>
#include <Functions.h>
using namespace std;


CartesianPlane::CartesianPlane(Window* window) : window(window) {
	
	vertices = vector<float>({
		0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		0.0f, -1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		-1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f
		});
	
	for (int x = 0; x < window->width; x = x + 10) {
		float normalizedX = pixelsToGL(x, window->width);

		vertices.insert(vertices.end(), {
				normalizedX, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.1f,
				normalizedX, -1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.1f,
			});
	};
	
	for (int y = 0; y < window->width; y = y + 10) {
		float normalizedY = pixelsToGL(y, window->height);

		vertices.insert(vertices.end(), {
				 1.0f, normalizedY, 0.0f, 1.0f, 1.0f, 1.0f, 0.1f,
				-1.0f, normalizedY, 0.0f, 1.0f, 1.0f, 1.0f, 0.1f,
			});
	};

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	
}

CartesianPlane::~CartesianPlane(){}

void CartesianPlane::render() {
	glBindVertexArray(vao);
	glDrawArrays(GL_LINES, 0, vertices.size() / 7);
	
}