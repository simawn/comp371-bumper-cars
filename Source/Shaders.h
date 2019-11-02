#pragma once
#include <string>
using namespace std;

class Shaders {
public:
	static Shaders& getInstance();
	static int currentShaderProgram;
	
private:
	Shaders();
	static Shaders* instance;
	string readFile(string filePath);
	int compileAndLinkShaders(const char* vertexShaderSource, const char* fragmentShaderSource);
	int colorShaderProgram;
	int texturedShaderProgram;
	int shadowShaderProgram;
};