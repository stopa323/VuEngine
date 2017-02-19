/*
 * FShaderManager.cpp
 *
 *  Created on: Feb 18, 2017
 *      Author: root
 */

#include "FShaderManager.h"


VkVertexInputBindingDescription SVertex::GetBindingDesctiption() {
	VkVertexInputBindingDescription binding_description = {};
	binding_description.binding		= 0;
	binding_description.stride		= sizeof( SVertex );
	binding_description.inputRate	= VK_VERTEX_INPUT_RATE_VERTEX; // data entry per vertex

	return binding_description;
}

TVertex2AttrArray SVertex::GetAttributeDescription() {
	TVertex2AttrArray attribute_description = {};

	/* position description */
	attribute_description[0].binding	= 0;
	attribute_description[0].location	= 0; // location in vertex shader
	attribute_description[0].format		= VK_FORMAT_R32G32_SFLOAT;
	attribute_description[0].offset		= offsetof( SVertex, position );

	/* color description */
	attribute_description[1].binding	= 0;
	attribute_description[1].location	= 1; // location in vertex shader
	attribute_description[1].format		= VK_FORMAT_R32G32B32A32_SFLOAT;
	attribute_description[1].offset		= offsetof( SVertex, color );

	return attribute_description;
}

FShaderManager::FShaderManager() {
	// TODO Auto-generated constructor stub

}

FShaderManager::~FShaderManager() {
	// TODO Auto-generated destructor stub
}

