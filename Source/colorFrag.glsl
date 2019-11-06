#version 330 core
uniform vec3 diffuseColor; //overwrites other colors

out vec4 FragColor;
void main() {
	FragColor = vec4(diffuseColor.r, diffuseColor.g, diffuseColor.b, 1.0f);
}