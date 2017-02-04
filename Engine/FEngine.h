/*
 * FEngine.h
 *
 *  Created on: Feb 4, 2017
 *      Author: root
 */

#ifndef ENGINE_FENGINE_H_
#define ENGINE_FENGINE_H_

#include "Window/FWindow.h"
#include <cstdint>
#include <memory>


enum class EEngineResult : uint8_t {
	SUCCESS						= 0,
	FAIL						= 1
};


class FEngine {
public:
	FEngine();
	virtual ~FEngine();

	void Initialize();

	/** Getters/Setters **/

private:
	EEngineResult createWindow();
	EEngineResult createInputManager();
	EEngineResult createEngineLoop();

	// Todo: try to make this const ptr
	std::shared_ptr<FWindow>			_window;
};

#endif /* ENGINE_FENGINE_H_ */
