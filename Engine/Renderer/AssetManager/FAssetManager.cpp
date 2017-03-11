/*
 * FAssetManager.cpp
 *
 *  Created on: Mar 11, 2017
 *      Author: root
 */

#include "FAssetManager.h"

FAssetManager::FAssetManager() { }

FAssetManager::~FAssetManager() { }

ELoadResult FAssetManager::LoadModel3D(const std::string& meshPath,
		const std::string& texturePath) {

}

ELoadResult FAssetManager::LoadMesh(const std::string& meshPath) {

}

ELoadResult FAssetManager::LoadTexture3D(const std::string& texturePath) {

}

bool FAssetManager::isModelLoaded(const size_t& uuid) {

}

bool FAssetManager::isTexture2DLoaded(const size_t& uuid) {

}

bool FAssetManager::isMeshLoaded(const size_t& uuid) {

}
