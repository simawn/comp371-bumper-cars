#pragma once

#include <glm/glm.hpp>
#include <cstring>
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>

bool loadOBJ2(
	const char * path,
	std::vector<int> & vertexIndices,
	std::vector<glm::vec3> & temp_vertices,
	std::vector<glm::vec3> & out_normals,
	std::vector<glm::vec2> & out_uvs);
