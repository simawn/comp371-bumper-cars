#pragma once
#include <string>
using namespace std;

extern int colorShaderProgram;
extern int texturedShaderProgram;
extern int shadowShaderProgram;

class Shaders {
public:
	static Shaders& getInstance();
private:
	Shaders();
	static Shaders* instance;
	string readFile(string filePath);
	int compileAndLinkShaders(const char* vertexShaderSource, const char* fragmentShaderSource);
};