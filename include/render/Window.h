#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
class Window {
public:
	GLFWwindow* window;
	GLuint shaderProgram;
	int width, height;
	const char* title;
	Window(int w, int h, const char* title);
	~Window();
	int init();

	
};