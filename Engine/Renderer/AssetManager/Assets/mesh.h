/*
 * mesh.h
 *
 *  Created on: Mar 11, 2017
 *      Author: root
 */

#ifndef ENGINE_RENDERER_ASSETMANAGER_ASSETS_MESH_H_
#define ENGINE_RENDERER_ASSETMANAGER_ASSETS_MESH_H_

#include <glm/glm.hpp>
#include <vector>

struct SVertex {
	glm::vec3	Position;
	glm::vec3 	Color;  // Todo: Consider Color as an option
};

// Todo: Consider replacing SMesh with template to utilize std::array instead
// of std::vector
struct SMesh {
	std::vector<SVertex>	Vertices;
	std::vector<uint16_t>	Indices;
	size_t					UUID;
};

#endif /* ENGINE_RENDERER_ASSETMANAGER_ASSETS_MESH_H_ */
