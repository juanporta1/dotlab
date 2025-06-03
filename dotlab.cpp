#include <Window.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <chrono>
#include <Ball.h>
#include <CartesianPlane.h>
#include <Vector2D.h>
using namespace std;
int main()
{
	int w = 1280;
	int h = 720;
	const char* title = "Dotlab";
	Window window(w, h, title);

	window.init();


	auto lastFrame = chrono::high_resolution_clock::now();
	Ball b(700.0f, 400.0f, 50.0f, 255.0f, 255.0f, 255.0f, &window);
	//b.accY = -9.81f;

	Vector2D vec1(200.0f, 0.0f, 255.0f, 0.0f, 0.0f, &window);
	CartesianPlane cp = CartesianPlane(&window);
	while (!glfwWindowShouldClose(window.window)) {
		auto currentFrame = chrono::high_resolution_clock::now();
		chrono::duration<float> delta = currentFrame - lastFrame;
		float dt = delta.count();
		lastFrame = currentFrame;
		
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(window.shaderProgram);

		/*b.update(dt);
		b.render();*/
		cp.render();
		vec1.render();
		glfwSwapBuffers(window.window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
