/*
 * FShaderManager.h
 *
 *  Created on: Feb 18, 2017
 *      Author: root
 */

#ifndef ENGINE_RENDERER_FSHADERMANAGER_H_
#define ENGINE_RENDERER_FSHADERMANAGER_H_

#include <vulkan/vulkan.h>
#include <glm/glm.hpp>
#include <array>

typedef std::array<VkVertexInputAttributeDescription, 2> TVertex2AttrArray;

struct SVertex {
	glm::vec2		position;
	glm::vec3		color;

	static VkVertexInputBindingDescription GetBindingDesctiption();
	static TVertex2AttrArray GetAttributeDescription();
};


class FShaderManager {
public:
	FShaderManager();
	virtual ~FShaderManager();

	// Todo: Implement
	void LoadShader();
	void CompileShader();
};

#endif /* ENGINE_RENDERER_FSHADERMANAGER_H_ */
