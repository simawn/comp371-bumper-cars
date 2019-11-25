// Collisions using SAT (Separating Axis Theorem)
// Source refered: https://www.youtube.com/watch?v=IELWpIGtjRg

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

vec2 Collision::collisionCheck(Model* model) {
	//Minimum translation vectors on collision
	vector<vec2> mtv;

	tuple<Model*, vec2, vec2, vec2, vec2> modelCoord = getCoordsFor(model);
	tuple<vec2, vec2> modelUniqueNorms = getUniqueNormals(get<1>(modelCoord), get<2>(modelCoord), get<3>(modelCoord), get<4>(modelCoord));
	
	vec2 allCoordsModel[] = {
			get<1>(modelCoord),
			get<2>(modelCoord),
			get<3>(modelCoord),
			get<4>(modelCoord),
		};

	//Overlap flag
	bool hasOverlap = true;

	//Check for car collision
	for (Model* other : collisionObjects) {
		mtv.clear();
		hasOverlap = true;

		if (other == model) continue;
		
		tuple<Model*, vec2, vec2, vec2, vec2> otherCoord = getCoordsFor(other);
		
		tuple<vec2, vec2> otherUniqueNorms = getUniqueNormals(get<1>(otherCoord), get<2>(otherCoord), get<3>(otherCoord), get<4>(otherCoord));
		
		//Compile data
		vec2 allNorms[] = { 
			get<0>(modelUniqueNorms),
			get<1>(modelUniqueNorms),

			get<0>(otherUniqueNorms),
			get<1>(otherUniqueNorms)
		};

		vec2 allCoordsOther[] = {
			get<1>(otherCoord),
			get<2>(otherCoord),
			get<3>(otherCoord),
			get<4>(otherCoord),
		};

		//Axis checks
		for (int i = 0; i < 4; i++) { //Axis

			//Store scalars for intersection check
			float scalarModel[4] = {};
			float scalarOther[4] = {};

			for (int j = 0; j < 4; j++) { //Pts
				scalarModel[j] = dot(allNorms[i], allCoordsModel[j]);
				scalarOther[j] = dot(allNorms[i], allCoordsOther[j]);
			}

			float maxScalarModel = *max_element(scalarModel, scalarModel + 4);
			float minScalarModel = *min_element(scalarModel, scalarModel + 4);
			float maxScalarOther = *max_element(scalarOther, scalarOther + 4);
			float minScalarOther = *min_element(scalarOther, scalarOther + 4);

			//No collision -> no overlap. Stop checking axis, do not check mtv, go to next comparison model
			if (minScalarOther > maxScalarModel || maxScalarOther < minScalarModel) {
				hasOverlap = false;
				break;
			}

			float distance1 = abs(maxScalarOther - minScalarModel);
			float distance2 = abs(maxScalarModel - minScalarOther);

			mtv.push_back(allNorms[i] * (distance1 < distance2 ? distance1 : -distance2));

		} //Axis check stop

		//Returns the axis with the least overlap. This determines the car behaviour on collision
		if (hasOverlap) {
			float shortestLength = -1;
			vec2 minimumVector = vec2(0, 0);

			for (vec2 v : mtv) {
				float lengthV = length(v);
				if (shortestLength == -1 || lengthV < shortestLength) {
					shortestLength = lengthV;
					minimumVector = v;
				}
			}
			return minimumVector;
		}
	} //Other model check end

	return vec2(0, 0);
}

Collision::Collision() {}

Collision::~Collision() {}

//Model, topLeft, topRight, bottomLeft, bottomRight
tuple<Model*, vec2, vec2, vec2, vec2> Collision::getCoordsFor(Model* model) {
	//Car length: 5
	//Car width: 7.5
	float centerX = model->GetPosition().x;
	float centerZ = model->GetPosition().z;
	float rotation = model->GetRotationAngle();
	float halfWidth = 4.5 / 2.0;
	float halfHeight = 7.5 / 2.0;

	float coords[8] = {  
		-halfWidth, //topLeftX
		halfHeight, //topLeftZ
		halfWidth, //topRightX
		halfHeight, //topRightZ
		-halfWidth, //botLeftX
		-halfHeight, //botLeftZ
		halfWidth, //botRightX
		-halfHeight //botRightZ
	};

	//Apply rotation to coords from origin, then add coords to car center
	for (int i = 0; i < 8; i += 2) {
		vec2 newXZ = rotate(vec2(coords[i], coords[i + 1]), radians(rotation));
		coords[i] = newXZ.x + centerX;
		coords[i + 1] = newXZ.y + centerZ;
	}

	return make_tuple(model,	vec2(coords[0], coords[1]), //topLeft
								vec2(coords[2], coords[3]), //topRight
								vec2(coords[4], coords[5]), //botLeft
								vec2(coords[6], coords[7]));//botRight
}

tuple<vec2, vec2> Collision::getUniqueNormals(vec2 topLeft, vec2 topRight, vec2 bottomLeft, vec2 bottomRight) {
	//Calculate slope

	float a1 = topLeft.y - topRight.y;
	float b1 = topLeft.x - topRight.x;
	vec2 n1 = a1 == 0 || b1 == 0 ? vec2(0, 1) : vec2(1, -1 / (a1 / b1));

	float a2 = topLeft.y - bottomLeft.y;
	float b2 = topLeft.x - bottomLeft.x;
	vec2 n2 = a2 == 0 || b2 == 0 ? vec2(-1, 0) : vec2(1, -1 / (a2 / b2));

	return make_tuple(normalize(n1), normalize(n2));
}

void Collision::debug() {
	tuple<Model*, vec2, vec2, vec2, vec2> positionData = getCoordsFor(collisionObjects.front());
	cout << "Model: " << get<0>(positionData) << endl;
	cout << "Model center: " << to_string(get<0>(positionData)->GetPosition()) << endl;
	cout << "Model rotation: " << get<0>(positionData)->GetRotationAngle() << endl;
	cout << "topLeft: " << to_string(get<1>(positionData)) << endl;
	cout << "topRight: " << to_string(get<2>(positionData)) << endl;
	cout << "botLeft: " << to_string(get<3>(positionData)) << endl;
	cout << "botRight: " << to_string(get<4>(positionData)) << endl;
	
	tuple<vec2, vec2> norms = getUniqueNormals(get<1>(positionData), get<2>(positionData), get<3>(positionData), get<4>(positionData));
	cout << "Unique norm 1: " << to_string(get<0>(norms)) << endl;
	cout << "Unique norm 2: " << to_string(get<1>(norms)) << endl;

	cout << endl;
}
