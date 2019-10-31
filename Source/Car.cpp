#include "Car.h"
#include "Renderer.h"
#include "Shaders.h"
#include <iostream>

Car::Car() {
	//worldMatrixLocation = glGetUniformLocation(shaderProgram, "worldMatrix");
	carRotation(0); //Fixes relative positioning
	srand(time(0));
}

void Car::draw(int shaderProgram) {
	//spinningAngle *= dt;

	//Set the color to red for the car
	//mainColor = vec3(0.9f, 0.0f, 0.0f);
	//glUniform3fv(mainColorUniformLocation, 1, &mainColor[0]);

	/*
	if (!enableTexture) { //Affects all colours below, except wheels
		glUseProgram(colorShaderProgram);
		setColor(vec3(0.9f, 0.0f, 0.0f), colorShaderProgram, 1);
	} else {
		
		
	}
	*/
	if (shaderProgram == Shaders::texturedShaderProgram) {
		Renderer::useTexture(Renderer::textureMap["RED"]);
		Renderer::matProperties(3.0f, 128.0f, vec3(0.39f, 0.27f, 0.36f));
	}
	if (shaderProgram == Shaders::colorShaderProgram) {
		Renderer::setColor(vec3(0.9f, 0.0f, 0.0f), Shaders::colorShaderProgram, 1);
	}
	//Car Body
	mat4 carBody = translate(mat4(1.0f), posCarBody) * rotate(mat4(1.0f), radians(rotCarBody), vec3(0.0f, 1.0f, 0.0f)) * scale(mat4(1.0f), scaleCarBody);
	Renderer::setWorldMatrix(shaderProgram, carBody);
	glDrawArrays(mode, 0, 36);


	//mainColor = vec3(0.8f, 0.0f, 0.0f);
	//glUniform3fv(mainColorUniformLocation, 1, &mainColor[0]);
	if (shaderProgram == Shaders::colorShaderProgram) {
		Renderer::setColor(vec3(0.8f, 0.0f, 0.0f), Shaders::colorShaderProgram, 1);
	}
	Renderer::useTexture(Renderer::textureMap["RED"]);
	//Car bumper front (Bonnet)
	mat4 carBumperFront = translate(mat4(1.0f), posCarBumperFront) * rotate(mat4(1.0f), radians(rotCarBumperFront), vec3(0.0f, 1.0f, 0.0f)) * scale(mat4(1.0f), scaleCarBumperFront);
	//glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &carBumperFront[0][0]);
	Renderer::setWorldMatrix(shaderProgram, carBumperFront);
	glDrawArrays(mode, 0, 36);

	//Car bumper back (Trunk)
	mat4 carBumperBack = translate(mat4(1.0f), posCarBumperBack) * rotate(mat4(1.0f), radians(rotCarBumperBack), vec3(0.0f, 1.0f, 0.0f)) * scale(mat4(1.0f), scaleCarBumperBack);
	//glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &carBumperBack[0][0]);
	Renderer::setWorldMatrix(shaderProgram, carBumperBack);
	glDrawArrays(mode, 0, 36);

	//mainColor = vec3(0.95f, 0.0f, 0.0f);
	//glUniform3fv(mainColorUniformLocation, 1, &mainColor[0]);
	if (shaderProgram == Shaders::colorShaderProgram) {
		Renderer::setColor(vec3(0.95f, 0.0f, 0.0f), Shaders::colorShaderProgram, 1);
	}
	Renderer::useTexture(Renderer::textureMap["RED"]);
	//Car roof
	mat4 carRoof = translate(mat4(1.0f), posCarRoof) * rotate(mat4(1.0f), radians(rotCarRoof), vec3(0.0f, 1.0f, 0.0f)) * scale(mat4(1.0f), scaleCarRoof);
	//glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &carRoof[0][0]);
	Renderer::setWorldMatrix(shaderProgram, carRoof);
	glDrawArrays(mode, 0, 36);

	//Might be needed for a fix.
	/*
	mat4 extra = scale(mat4(1.0f), vec3(0.0f));
	setWorldMatrix(colorShaderProgram, extra);
	glDrawArrays(mode, 0, 0);
	*/

	//Car wheel front left
	mat4 carWheelFrontLeft = translate(mat4(1.0f), posCarWheelFrontLeft) * rotate(mat4(1.0f), radians(rotCarWheelFrontLeft), vec3(0.0f, 1.0f, 0.0f)) * rotate(mat4(1.0f), radians(-spinningAngle), vec3(0.0f, 0.0f, 1.0f)) * scale(mat4(1.0f), scaleCarWheelBackLeft);
	//glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &carWheelFrontLeft[0][0]);
	//glDrawArrays(mode, 0, 36);
	drawWheel(carWheelFrontLeft, shaderProgram);

	//Car wheel front right
	mat4 carWheelFrontRight = translate(mat4(1.0f), posCarWheelFrontRight) * rotate(mat4(1.0f), radians(rotCarWheelFrontRight), vec3(0.0f, 1.0f, 0.0f)) * rotate(mat4(1.0f), radians(-spinningAngle), vec3(0.0f, 0.0f, 1.0f)) * scale(mat4(1.0f), scaleCarWheelFrontRight);
	//glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &carWheelFrontRight[0][0]);
	//glDrawArrays(mode, 0, 36);
	drawWheel(carWheelFrontRight, shaderProgram);

	//Car wheel back left
	mat4 carWheelBackLeft = translate(mat4(1.0f), posCarWheelBackLeft) * rotate(mat4(1.0f), radians(rotCarWheelBackLeft), vec3(0.0f, 1.0f, 0.0f)) * rotate(mat4(1.0f), radians(-spinningAngle), vec3(0.0f, 0.0f, 1.0f)) * scale(mat4(1.0f), scaleCarWheelBackLeft);
	//glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &carWheelBackLeft[0][0]);
	//glDrawArrays(mode, 0, 36);
	drawWheel(carWheelBackLeft, shaderProgram);

	//Car wheel back right
	mat4 carWheelBackRight = translate(mat4(1.0f), posCarWheelBackRight) * rotate(mat4(1.0f), radians(rotCarWheelBackRight), vec3(0.0f, 1.0f, 0.0f)) * rotate(mat4(1.0f), radians(-spinningAngle), vec3(0.0f, 0.0f, 1.0f)) * scale(mat4(1.0f), scaleCarWheelBackRight);
	//glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &carWheelBackRight[0][0]);
	//glDrawArrays(mode, 0, 36);
	drawWheel(carWheelBackRight, shaderProgram);
}

void Car::scaleKey(int mode) {
	//0 scales up, any other int scale down

	const vec3 SCALE_RATE = mode == 0 ? vec3(1.001f, 1.001f, 1.001f) : vec3(0.999f, 0.999f, 0.999f);

	vec3 tempPosCarBody = posCarBody;

	//Scale
	posCarBody *= SCALE_RATE;

	scaleCarBody *= SCALE_RATE;
	scaleCarBumperFront *= SCALE_RATE;
	scaleCarBumperBack *= SCALE_RATE;
	scaleCarRoof *= SCALE_RATE;
	scaleCarWheelFrontLeft *= SCALE_RATE;
	scaleCarWheelFrontRight *= SCALE_RATE;
	scaleCarWheelBackLeft *= SCALE_RATE;
	scaleCarWheelBackRight *= SCALE_RATE;

	//Reset car its relative position before scaling (Without this, the car would translate as it scales)
	posCarBody.x = tempPosCarBody.x;
	posCarBody.z = tempPosCarBody.z;
	
	//carRotation recalculates the relative position of all parts
	carRotation(0);
}

void Car::randomPosition() {
	float randOffsetX = rand() % 100 + (-50);
	float randOffsetZ = rand() % 100 + (-50);

	posCarBody = vec3(randOffsetX, scaleCarBody.y / 2 + scaleCarWheelBackLeft.y / 2, randOffsetZ);

	//carRotation recalculates the relative position of all parts
	carRotation(0);
}

void Car::resetPosition() {
	posCarBody = vec3(0.0f, scaleCarBody.y / 2 + scaleCarWheelBackLeft.y / 2, 0.0f);
	carRotation(0);
}

void Car::renderMode(int type) {
	switch (type) {
	case 1:
		mode = GL_POINTS;
		break;
	case 2:
		mode = GL_LINES;
		break;
	default:
		mode = GL_TRIANGLES;
		break;
	}
}

void Car::move(int type) {
	const float SPEED_RATE = dt * 10;
	float move_dir = 0.0f;
	const float SPIN_RATE = dt * 100;

	//0: forward
	//1: backwards
	//2: left
	//3: right
	switch (type) {
	case 0: //Move forward
		move_dir = 0.0f;
		break;
	case 1: //Move backwards
		move_dir = 180.0f;
		break;
	case 2: //Turn left
		carRotation(SPIN_RATE);
		//move_dir = vec3(0.0f, 0.0f, -25.0f);
		break;
	case 3: //Turn right
		carRotation(-SPIN_RATE);
		//move_dir = vec3(0.0f, 0.0f, 25.0f);
		break;
	}
	if (type == 0 || type == 1) {
		//Using point in circle formula to calculate relative translation of the car
		float a = posCarBody.x;
		float b = posCarBody.z;
		float r = SPEED_RATE;
		posCarBody = vec3(
			a + r * cos(radians(rotCarBody + move_dir)),
			posCarBody.y,
			b + r * -sin(radians(rotCarBody + move_dir))
		);
	}
	carRotation(0);
}

Car::~Car() {
}

void Car::carRotation(float SPIN_RATE) {
	//Data for right front wheel
	float initialRelativePosWheelFrontRightZ = scaleCarBumperFront.z / 2.0f + scaleCarWheelFrontRight.z / 2.0f;
	float initialRelativePosWheelFrontRightX = scaleCarBody.x / 2.0f + scaleCarBumperFront.x / 4.0f;
	float initialAngleWheelFrontRight = atan(initialRelativePosWheelFrontRightZ / initialRelativePosWheelFrontRightX);
	float initialRadiusWheelFrontRight = sqrt(pow(initialRelativePosWheelFrontRightZ, 2) + pow(initialRelativePosWheelFrontRightX, 2));

	//For the left front wheel, it shares the same data as right front wheel but the starting angle is opposite

	//Data for right back wheel
	float initialRelativePosWheelBackRightZ = scaleCarBody.z / 2.0f + scaleCarWheelBackRight.z / 2.0f;
	float initialRelativePosWheelBackRightX = scaleCarBody.x / 2.0f;
	float initialAngleWheelBackRight = atan(initialRelativePosWheelBackRightZ / initialRelativePosWheelBackRightX);
	float initialRadiusWheelBackRight = sqrt(pow(initialRelativePosWheelBackRightZ, 2) + pow(initialRelativePosWheelBackRightX, 2));

	//Same as above, the left back wheel shares the same data as right but starting angle is opposite

	//Rotate car body
	rotCarBody += SPIN_RATE;

	//Rotate bumper front
	rotCarBumperFront += SPIN_RATE;
	//[a + r * cos(phi + theta), b + r * sin(phi + theta)]
	posCarBumperFront = vec3(
		//center point, radius, angle
		posCarBody.x + (scaleCarBody.x / 2 + scaleCarBumperFront.x / 2) * -cos(radians(rotCarBumperFront - 180)),
		scaleCarBumperFront.y / 2 + scaleCarWheelBackLeft.y / 2,
		posCarBody.z + (scaleCarBody.x / 2 + scaleCarBumperFront.x / 2) * sin(radians(rotCarBumperFront - 180))
	);

	//Rotate bumper back
	rotCarBumperBack += SPIN_RATE;
	posCarBumperBack = vec3(
		posCarBody.x - (scaleCarBody.x / 2 + scaleCarBumperBack.x / 2) * -cos(radians(rotCarBumperBack - 180)),
		scaleCarBumperBack.y / 2 + scaleCarWheelBackLeft.y / 2,
		posCarBody.z - (scaleCarBody.x / 2 + scaleCarBumperBack.x / 2) * sin(radians(rotCarBumperBack - 180))
	);

	rotCarRoof += SPIN_RATE;
	posCarRoof = vec3(posCarBody.x, scaleCarBody.y + scaleCarRoof.y / 2 + scaleCarWheelFrontLeft.y / 2, posCarBody.z); //Original posCarRoof.y divided by original posCarBody.y

	//Rotate wheels
	//We need a special starting angle for the wheel since they are offset from the car body

	rotCarWheelFrontLeft += SPIN_RATE;
	posCarWheelFrontLeft = vec3(
		posCarBody.x + (initialRadiusWheelFrontRight) * -cos(radians(rotCarWheelFrontLeft + 180.0f) - initialAngleWheelFrontRight),
		scaleCarWheelFrontLeft.y / 2,
		posCarBody.z + (initialRadiusWheelFrontRight)* sin(radians(rotCarWheelFrontLeft + 180.0f) - initialAngleWheelFrontRight)
	);

	rotCarWheelFrontRight += SPIN_RATE;
	posCarWheelFrontRight = vec3(
		posCarBody.x + (initialRadiusWheelFrontRight) * -cos(radians(rotCarWheelFrontRight + 180.0f) + initialAngleWheelFrontRight), //+ instead of -, same as above
		scaleCarWheelFrontRight.y / 2,
		posCarBody.z + (initialRadiusWheelFrontRight)* sin(radians(rotCarWheelFrontRight + 180.0f) + initialAngleWheelFrontRight)
	);

	rotCarWheelBackLeft += SPIN_RATE;
	posCarWheelBackLeft = vec3(
		posCarBody.x + (initialRadiusWheelBackRight) * -cos(radians(rotCarWheelBackLeft) + initialAngleWheelBackRight),
		scaleCarWheelFrontRight.y / 2,
		posCarBody.z + (initialRadiusWheelBackRight)* sin(radians(rotCarWheelBackLeft) + initialAngleWheelBackRight)
	);

	rotCarWheelBackRight += SPIN_RATE;
	posCarWheelBackRight = vec3(
		posCarBody.x + (initialRadiusWheelBackRight) * -cos(radians(rotCarWheelBackRight) - initialAngleWheelBackRight),
		scaleCarWheelFrontRight.y / 2,
		posCarBody.z + (initialRadiusWheelBackRight)* sin(radians(rotCarWheelBackRight) - initialAngleWheelBackRight)
	);
}

void Car::drawWheel(mat4 transformations, int shaderProgram) {
	//mainColor = vec3(0.4f, 0.4f, 0.4f);
	//glUniform3fv(mainColorUniformLocation, 1, &mainColor[0]);
	//setColor(vec3(0.4f, 0.4f, 0.4f));

	/*
	if (enableTexture) {
		
		setColor(vec3(0.4f, 0.4f, 0.4f), texturedShaderProgram, 0);
		matProperties(0.3f, 1.0f, vec3(0.4f, 0.4f, 0.4f));
	} else {
		glUseProgram(colorShaderProgram);
		setColor(vec3(0.4f, 0.4f, 0.4f), colorShaderProgram, 1);
	}
	*/
	if (shaderProgram == Shaders::colorShaderProgram) {
		Renderer::setColor(vec3(0.4f, 0.4f, 0.4f), Shaders::colorShaderProgram, 1);
	}

	if (shaderProgram == Shaders::texturedShaderProgram) {
		Renderer::useTexture(Renderer::textureMap["TIRE"]);
		Renderer::matProperties(0.3f, 1.0f, vec3(0.4f, 0.4f, 0.4f));
	}

	mat4 wheelControlPoint = transformations;
	
	mat4 wheelFront = wheelControlPoint;
	//glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &wheelFront[0][0]);
	Renderer::setWorldMatrix(shaderProgram, wheelFront);
	glDrawArrays(mode == GL_TRIANGLES ? GL_TRIANGLE_FAN : mode == GL_LINES ? GL_LINE_LOOP : mode, 36, 16);

	mat4 wheelBack = wheelControlPoint;
	//glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &wheelBack[0][0]);
	Renderer::setWorldMatrix(shaderProgram, wheelBack);
	glDrawArrays(mode == GL_TRIANGLES ? GL_TRIANGLE_FAN : mode == GL_LINES ? GL_LINE_LOOP : mode, 52, 16);

	mat4 wheelSide = wheelControlPoint;
	//glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &wheelSide[0][0]);
	Renderer::setWorldMatrix(shaderProgram, wheelSide);
	glDrawArrays(mode == GL_TRIANGLES ? GL_TRIANGLE_STRIP : mode, 68, 34);
}
