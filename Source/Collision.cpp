#include "Collision.h"

using namespace std;
using namespace glm;

Collision* Collision::instance = 0;
int Collision::count = 0;

Collision& Collision::getInstance() {
	if (instance == 0) instance = new Collision();
	return *instance;
}

void Collision::addObject(Model* model) {
	collisionObjects.push_back(model);
}

bool Collision::IsColliding(Model* model) {
	vector<tuple<Model*, float, float>> coords = getCoordsFor(model);
	vector<tuple<Model*, float, float>> otherCoords = getAllCoordsExcept(model);
	
	
	/* //Debug
	if (count % 600 == 0) {
		cout << "This coords:" << endl;
		for (auto const& coord : coords) {
			cout << get<0>(coord) << ": " << get<1>(coord) << " " << get<2>(coord) << endl;
		}
		cout << "====" << endl;
		cout << "Other coords:" << endl;
		for (auto const& coord : otherCoords) {
			cout << get<0>(coord) << ": " << get<1>(coord) << " " << get<2>(coord) << endl;
		}
		cout << endl;
	}
	
	*/
	vec3 modelPosition = model->GetPosition();
	vec2 modelCenterCoord = vec2(modelPosition.x, modelPosition.z);
	float radius = distance(modelCenterCoord, vec2(get<1>(coords.front()), get<2>(coords.front())));
	float radiusExtra = 0.2;

	vector<Model*> potentialColliders;

	for (auto const& coord : otherCoords) {
		if (find(potentialColliders.begin(), potentialColliders.end(), get<0>(coord)) != potentialColliders.end()) continue;

		float otherDistance = distance(modelCenterCoord, vec2(get<1>(coord), get<2>(coord)));
		if (otherDistance <= (radius + radiusExtra)) {
			potentialColliders.push_back(get<0>(coord));
		}
	}

	for (auto const& collider : potentialColliders) {
		int colliderRotation = (int) collider->GetRotationAngle() % 360;
		vector<tuple<Model*, float, float>> colliderCoords = getCoordsFor(collider);
		//Check curr points
		int iter = 0;
		for (auto const& curCarCoord : coords) {
			if (iter >= 2) break; //only checking the front points
			vec2 topLeft = vec2(get<1>(colliderCoords.front()), get<2>(colliderCoords.front()));
			vec2 botRight = vec2(get<1>(colliderCoords.back()), get<2>(colliderCoords.back()));
			vec2 point = vec2(get<1>(curCarCoord), get<2>(curCarCoord));
			//Transform
			float angleOffset = 360 - colliderRotation;
			topLeft = rotate(topLeft, radians(angleOffset));
			botRight = rotate(botRight, radians(angleOffset));
			point = rotate(point, radians(angleOffset));
			iter++;
			//if (isInRectangle(point, topLeft, botRight)) return true;
		}
	}


	count++;
	return false;
}

Collision::Collision() {}

vector<tuple<Model*, float, float>> Collision::getCoordsFor(Model * model) {
	//Car length: 5
	//Car width: 7.5
	float centerX = model->GetPosition().x;
	float centerZ = model->GetPosition().z;
	float rotation = model->GetRotationAngle();
	float halfWidth = 5.0 / 2.0;
	float halfHeight = 7.5 / 2.0;

	float coords[8] = { centerX - halfWidth, //topLeftX
						centerZ + halfHeight, //topLeftZ
						centerX + halfWidth, //topRightX
						centerZ + halfHeight, //topRightZ
						centerX - halfWidth, //botLeftX
						centerZ - halfHeight, //botLeftZ
						centerX + halfWidth, //botRightX
						centerZ - halfHeight //botRightZ
	};

	//Apply rotation to coords
	for (int i = 0; i < 8; i += 2) {
		vec2 newXZ = rotate(vec2(coords[i], coords[i + 1]), radians(rotation));
		coords[i] = newXZ.x;
		coords[i + 1] = newXZ.y;
	}

	//Build resulting tuples
	vector<tuple<Model*, float, float>> result;
	for (int i = 0; i < 8; i += 2) {
		tuple<Model*, float, float> item = make_tuple(model, coords[i], coords[i+1]);
		result.push_back(item);
	}

	return result;
}

vector<tuple<Model*, float, float>> Collision::getAllCoordsExcept(Model* model) {
	vector<tuple<Model*, float, float>> result;

	for (auto &const otherModel : collisionObjects) {
		if (otherModel == model) continue;
		vector<tuple<Model*, float, float>> data = getCoordsFor(otherModel);
		result.insert(result.end(), data.begin(), data.end());
	}

	return result;
}

tuple<vec2, vec2> Collision::getCornersFor(Model * model) {
	vector<tuple<Model*, float, float>> coords = getCoordsFor(model);
	vec2 topLeft = vec2(get<1>(coords.front()), get<2>(coords.front()));
	vec2 botRight = vec2(get<1>(coords.back()), get<2>(coords.back()));

	return make_tuple(topLeft, botRight);
}

bool Collision::isInRectangle(vec2 point, vec2 topLeft, vec2 botRight) {
	if (point.x > topLeft.x && point.x < botRight.x &&
		point.y < topLeft.y && point.y > botRight.y) {
		return true;
	}
	return false;
}

