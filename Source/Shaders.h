#pragma once
#include <string>
using namespace std;

class Shaders {
public:
	static Shaders& getInstance();
	static int colorShaderProgram;
	static int texturedShaderProgram;
	static int shadowShaderProgram;
private:
	Shaders();
	static Shaders* instance;
	string readFile(string filePath);
	int compileAndLinkShaders(const char* vertexShaderSource, const char* fragmentShaderSource);
};