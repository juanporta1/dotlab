#include <vector>
#include <Vector2D.h>
#include <VectorGroup2D.h>
#include <Window.h>
#include <Functions.h>
#include <iostream>
using namespace std;

VectorGroup2D::VectorGroup2D(vector<Vector2D*> vs, Window* w, VectorGroupOptions opt) : vectors(vs), window(w), options(opt), startX(w->width / 2), startY(w->height / 2),
mainVector(0.0f, 0.0f, startX, startY, 0.0f, 0.0f, 0.0f, w),
xComponent(0.0f, 0.0f, startX, startY, 255.0f, 0.0f, 0.0f, w),
yComponent(0.0f, 0.0f, startX, startY, 0.0f, 0.0f, 255.0f, w) {
	
	updateResulting();
	
}

VectorGroup2D::VectorGroup2D(float x, float y,vector<Vector2D*> vs, Window* w, VectorGroupOptions opt) : vectors(vs), window(w), options(opt), startX(x), startY(y),
mainVector(0.0f, 0.0f, startX, startY, 0.0f, 0.0f, 0.0f, w),
xComponent(0.0f, 0.0f, startX, startY, 255.0f, 0.0f, 0.0f, w),
yComponent(0.0f, 0.0f, startX, startY, 0.0f, 0.0f, 255.0f, w) {
	
	updateResulting();

}

VectorGroup2D::~VectorGroup2D() {}

void VectorGroup2D::render() {
	for (Vector2D* v : vectors) {
		v->render();
	}
	if (options.renderComponents) {
		if (mainVector.magnitude == 0.0f) 
		{
			xComponent.setMagnitude(0.0f);
			yComponent.setMagnitude(0.0f);
		}

		xComponent.render();
		yComponent.render();
	}
	mainVector.render();

}

void VectorGroup2D::updateResulting() {
	float totalXComponent = 0.0f;
	float totalYComponent = 0.0f;
	
	for(Vector2D* v : vectors) {
		v->move(startX, startY);
		vec2 components = v->getComponents();
		totalXComponent += GLMagnitudeToPixels(components.x, window->width);
		totalYComponent += GLMagnitudeToPixels(components.y, window->height);
	}

	float mainMagnitude = sqrt(totalXComponent * totalXComponent + totalYComponent * totalYComponent);
	float mainAngle = atan2(totalYComponent, totalXComponent);
	mainVector.setDirection(radsToDegrees(mainAngle));
	mainVector.setMagnitude(mainMagnitude);
	mainVector.move(startX, startY);


	vec2 mainComponentMagnitude = mainVector.getComponents();
	
	float xComponentDirection = (mainComponentMagnitude.x >= 0.0f) ? 0.0f : 180.0f;
	float yComponentDirection = (mainComponentMagnitude.y >= 0.0f) ? 90.0f : 270.0f;
	xComponent.setMagnitude(GLMagnitudeToPixels(abs(mainComponentMagnitude.x), window->width));
	xComponent.setDirection(xComponentDirection);
	xComponent.move(startX, startY);
	yComponent.setMagnitude(GLMagnitudeToPixels(abs(mainComponentMagnitude.y), window->height));
	yComponent.setDirection(yComponentDirection);
	yComponent.move(startX, startY);
}

void VectorGroup2D::addVector(Vector2D* v) {
	vectors.push_back(v);
	updateResulting();
}

void VectorGroup2D::move(float x, float y) {
	startX = x;
	startY = y;
	updateResulting();
}