#include <vector>
#include <Vector2D.h>
#include <VectorGroup2D.h>
#include <Window.h>
#include <Functions.h>
#include <iostream>
using namespace std;

VectorGroup2D::VectorGroup2D(vector<Vector2D> vs, Window* w, VectorGroupOptions opt) : vectors(vs), window(w) {
	options = opt;
	getSum();
	
}

VectorGroup2D::~VectorGroup2D() {}

void VectorGroup2D::render() {
	for (Vector2D& v : vectors) {
		v.render();
	}
	mainVector.render();
	if (options.renderComponents) {
		xComponent.render();
		yComponent.render();
	}
}

void VectorGroup2D::getSum() {
	float totalXComponent = 0.0f;
	float totalYComponent = 0.0f;
	
	for(Vector2D& v : vectors) {
		vec2 components = v.getComponents();
		cout << components.x << " " << components.y << endl;
		totalXComponent += GLMagnitudeToPixels(components.x, window->width);
		totalYComponent += GLMagnitudeToPixels(components.y, window->height);
	}

	float mainMagnitude = sqrt(totalXComponent * totalXComponent + totalYComponent * totalYComponent);
	float mainAngle = atan2(totalYComponent, totalXComponent);

	mainVector = Vector2D(mainMagnitude, radsToDegrees(mainAngle), 255.0f, 0.0f, 0.0f, window);
	vec2 mainComponentMagnitude = mainVector.getComponents();
	
	float xComponentDirection = 180.0f;
	float yComponentDirection = 90.0f;
	if(mainVector.direction < 90.0f || mainVector.direction > 270.0f){
		xComponentDirection = 0.0f;
	}

	if (mainVector.direction > 180.0f) {
		yComponentDirection = 270.0f;
	}

	xComponent = Vector2D(GLMagnitudeToPixels(mainComponentMagnitude.x, window->width), xComponentDirection, 0.0f, 255.0f, 0.0f, window);
	yComponent = Vector2D(GLMagnitudeToPixels(mainComponentMagnitude.y, window->height), yComponentDirection, 0.0f, 0.0f, 255.0f, window);
}

void VectorGroup2D::addVector(Vector2D v) {
	vectors.push_back(v);
	getSum();
}