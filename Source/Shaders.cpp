#include "Shaders.h"
#include <string>
#include <fstream>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/common.hpp>

using namespace std;

Shaders* Shaders::instance = 0; 
int Shaders::currentShaderProgram = 0;
int Shaders::shadowShaderProgram = 0;
int Shaders::sceneShaderProgram = 0;

Shaders& Shaders::getInstance() {
	if (instance == 0) instance = new Shaders();
	return *instance;
}

void Shaders::setCurrentShaderProgram(int program) {
	currentShaderProgram = program;
}

Shaders::Shaders() {
	string tempVert[] = {	readFile("../Source/shadowVert.glsl"), 
							readFile("../Source/sceneVert.glsl")};

	string tempFrag[] = {	readFile("../Source/shadowFrag.glsl"), 
							readFile("../Source/sceneFrag.glsl")};

	shadowShaderProgram = compileAndLinkShaders(tempVert[0].c_str(), tempFrag[0].c_str());
	sceneShaderProgram = compileAndLinkShaders(tempVert[1].c_str(), tempFrag[1].c_str());

	currentShaderProgram = sceneShaderProgram;
}

string Shaders::readFile(string filePath) {
	string output;
	ifstream vertexSource(filePath);
	string line;
	while (getline(vertexSource, line)) {
		output += line;
		output += "\r\n";
	}
	return output;
}

int Shaders::compileAndLinkShaders(const char* vertexShaderSource, const char* fragmentShaderSource) {
	// compile and link shader program
	// return shader program id
	// ------------------------------------

	// vertex shader
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// check for shader compile errors
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// fragment shader
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// check for shader compile errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// link shaders
	int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// check for linking errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return shaderProgram;
}
