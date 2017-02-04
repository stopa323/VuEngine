/*
 * FEngine.h
 *
 *  Created on: Feb 4, 2017
 *      Author: root
 */

#ifndef ENGINE_FENGINE_H_
#define ENGINE_FENGINE_H_

#include "Window/FWindow.h"
#include "FEngineLoop.h"
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
	std::shared_ptr<FWindow> GetWindow() const;
	std::shared_ptr<FInputManager> GetInputManager() const;
	std::shared_ptr<FEngineLoop> GetEngineLoop() const;

private:
	EEngineResult createWindow();
	EEngineResult createInputManager();
	EEngineResult createEngineLoop();

	// Todo: try to make this const ptr
	std::shared_ptr<FWindow>			_window;
	std::shared_ptr<FInputManager>		_input_manager;
	std::shared_ptr<FEngineLoop>		_engine_loop;
};

#endif /* ENGINE_FENGINE_H_ */
