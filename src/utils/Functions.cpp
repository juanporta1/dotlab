#include <Functions.h>
#include <Window.h>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
using namespace std;
float pixelsToGL(float value,int wS ) {
	return ((value / wS) * 2.0f) - 1.0f;
}

float GLToPixels(float value, int wS) {
    return ((value + 1.0f) / 2.0f) * wS;
}
float pixelMagnitudeToGL(float value, int wS) {
    return value * 2.0f / wS;
}
float GLMagnitudeToPixels(float value, int wS) {
	return value * wS / 2.0f;
}

float degreesToRads(float degrees) {
        return degrees * M_PI / 180.0f;
}
float radsToDegrees(float radians) {
    return radians * 180.0f / M_PI ;
}

float rgbToGL(float value) {
	return value / 255.0f;
}


string readFile(const char* filepath) {
    ifstream file(filepath);
    if (!file.is_open()) {
        cerr << "Failed to open " << filepath << endl;
        return "";
    }
    stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}
