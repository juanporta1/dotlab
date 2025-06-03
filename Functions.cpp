#include <Functions.h>
#include <Window.h>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
using namespace std;
float pixelsToGL(float value,int wS ) {
	return ((value / wS) * 2.0f) - 1.0f;
}

float rgbToGL(float value) {
	return (value / 255.0f);
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
