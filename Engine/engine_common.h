/*
 * engine_common.h
 *
 *  Created on: Mar 11, 2017
 *      Author: root
 */

#ifndef ENGINE_ENGINE_COMMON_H_
#define ENGINE_ENGINE_COMMON_H_

#include "InputManager/FInputManager.h"
#include "Window/FWindow.h"
#include "Renderer/FSimpleRenderer.h"
#include "PhysicsEngine/FPhysicsEngine.h"

#include <cstdint>
#include <memory>

struct SEngineContext {
	std::shared_ptr<FInputManager>		InputManager;
	std::shared_ptr<FWindow>			Window;
	std::shared_ptr<FSimpleRenderer>	RenderEngine;
	std::shared_ptr<FPhysicsEngine>		PhysicsEngine;
};


#endif /* ENGINE_ENGINE_COMMON_H_ */
