/*
 * FAssetManager.h
 *
 *  Created on: Mar 11, 2017
 *      Author: root
 */

#ifndef ENGINE_RENDERER_ASSETMANAGER_FASSETMANAGER_H_
#define ENGINE_RENDERER_ASSETMANAGER_FASSETMANAGER_H_

#include "Assets/model3d.h"
#include <vector>
#include <string>
#include <unordered_map>

enum class ELoadResult : uint8_t {
	UNKNOWN				= 0,
	SUCCESS_LOADED		= 1,
	SUCCESS_DUPLICATE	= 2,
	FAIL				= 3
};

typedef std::unordered_map<size_t, SMesh>		TMeshIDMap;
typedef std::unordered_map<size_t, SModel3D>	TModel3DIDMap;
typedef std::unordered_map<size_t, STexture2D>	TTexture2DIDMap;

class FAssetManager {
public:
	FAssetManager();
	virtual ~FAssetManager();

	ELoadResult LoadModel3D(const std::string& meshPath,
							const std::string& texturePath);
	ELoadResult LoadMesh(const std::string& meshPath);
	ELoadResult LoadTexture3D(const std::string& texturePath);

private:
	bool isModelLoaded(const size_t& uuid);
	bool isTexture2DLoaded(const size_t& uuid);
	bool isMeshLoaded(const size_t& uuid);

	TMeshIDMap				_loaded_meshes;
	TTexture2DIDMap			_loaded_textures2d;
	TModel3DIDMap			_loaded_models3d;
};

#endif /* ENGINE_RENDERER_ASSETMANAGER_FASSETMANAGER_H_ */
