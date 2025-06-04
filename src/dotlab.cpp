#include <Window.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <chrono>
#include <Ball.h>
#include <CartesianPlane.h>
#include <Vector2D.h>
#include <VectorGroup2D.h>
using namespace std;
int main()
{
	int w = 1280;
	int h = 720;
	const char* title = "Dotlab";
	Window window(w, h, title);

	window.init();
	//Declaracion de objetos
	Vector2D vec1(200.0f, 70.0f, 255.0f, 255.0f, 0.0f, 1.0f, &window);
	Vector2D vec2(100.0f, 40.0f, 0.0f, 255.0f, 0.0f, 1.0f, &window);

	VectorGroup2D vecGroup1(vector<Vector2D>({vec1, vec2}), &window);
	CartesianPlane cp = CartesianPlane(&window);
	//Ball b(700.0f, 400.0f, 50.0f, 255.0f, 255.0f, 255.0f, &window);
	//b.accY = -9.81f;


	auto lastFrame = chrono::high_resolution_clock::now();
	/*float rotateFlat = 0.0f;
	bool grow = false;*/



	while (!glfwWindowShouldClose(window.window)) {
		auto currentFrame = chrono::high_resolution_clock::now();
		chrono::duration<float> delta = currentFrame - lastFrame;
		float dt = delta.count();
		lastFrame = currentFrame;
		//rotateFlat += dt;

		/*if (rotateFlat >= 0.0001f) {
			vec1.rotate(-1.0f);
			rotateFlat = 0.0f;
			if (!grow)
				vec1.setMagnitude(vec1.magnitude - 0.08f);
			else if (grow)
				vec1.setMagnitude(vec1.magnitude + 0.08f);

			if (vec1.magnitude <= 30.f) grow = true;
			else if (vec1.magnitude >= 200.0f) grow = false;
		}*/

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(window.shaderProgram);

		cp.render();
		vecGroup1.render();

		glfwSwapBuffers(window.window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
