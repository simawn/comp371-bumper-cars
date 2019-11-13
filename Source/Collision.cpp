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
	
	
	if (count % 600 == 0) {
		cout << "This coords:" << endl;
		for (auto const& coord : coords) {
			cout << get<0>(coord) << ": " << get<1>(coord) << " " << get<2>(coord) << endl;
		}
		cout << " " << endl;
		cout << "Other coords:" << endl;
		for (auto const& coord : otherCoords) {
			cout << get<0>(coord) << ": " << get<1>(coord) << " " << get<2>(coord) << endl;
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

