#pragma once
#include <Window.h>
#include <string>
using namespace std;
float pixelsToGL(float value, int window);
float GLToPixels(float value, int window);
float rgbToGL(float value);
string readFile(const char* filepath);
float pixelMagnitudeToGL(float value, int wS);
float GLMagnitudeToPixels(float value, int wS);
float degreesToRads(float degrees);
float radsToDegrees(float radians);