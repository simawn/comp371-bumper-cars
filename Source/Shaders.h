#pragma once
#include <string>
using namespace std;

class Shaders {
public:
	static Shaders& getInstance();
	static int currentShaderProgram;
	static void setCurrentShaderProgram(int program);
	static int shadowShaderProgram;
	static int sceneShaderProgram;
private:
	Shaders();
	static Shaders* instance;
	string readFile(string filePath);
	int compileAndLinkShaders(const char* vertexShaderSource, const char* fragmentShaderSource);
};
