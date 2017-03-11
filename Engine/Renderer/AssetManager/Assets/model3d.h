/*
 * model3d.h
 *
 *  Created on: Mar 11, 2017
 *      Author: root
 */

#ifndef ENGINE_RENDERER_ASSETMANAGER_ASSETS_MODEL3D_H_
#define ENGINE_RENDERER_ASSETMANAGER_ASSETS_MODEL3D_H_

#include "mesh.h"
#include "texture.h"

struct SModel3D {
	const SMesh&		Mesh;
	const STexture2D&	Texture2D;
	const size_t&		UUID;
};


#endif /* ENGINE_RENDERER_ASSETMANAGER_ASSETS_MODEL3D_H_ */
