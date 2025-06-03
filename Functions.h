#pragma once
#include <Window.h>
#include <string>
using namespace std;
float pixelsToGL(float value, int window);
float rgbToGL(float value);
string readFile(const char* filepath);