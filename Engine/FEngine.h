/*
 * FEngine.h
 *
 *  Created on: Feb 4, 2017
 *      Author: root
 */

#ifndef ENGINE_FENGINE_H_
#define ENGINE_FENGINE_H_

#include "Window/FWindow.h"
#include "engine_common.h"
#include "FEngineLoop.h"
#include "Renderer/FSimpleRenderer.h"


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
	std::shared_ptr<FPhysicsEngine> GetPhysicsEngine() const;

	std::shared_ptr<FSimpleRenderer>	_renderer;

private:
	// Todo: consider some Factory
	EEngineResult createWindow();
	EEngineResult createInputManager();
	EEngineResult createEngineLoop();
	EEngineResult createRenderer();
	EEngineResult createChrono();
	EEngineResult createPhysicsEngine();

	// Todo: try to make this const ptr
	// Todo: redesign necessary - whats the point initializing elements
	// in Engine just to pass reference to EngineLoop
	std::shared_ptr<FWindow>			_window;
	std::shared_ptr<FInputManager>		_input_manager;
	std::shared_ptr<FEngineLoop>		_engine_loop;
	//std::shared_ptr<FSimpleRenderer>	_renderer;
	std::shared_ptr<FChrono>			_chrono;
	std::shared_ptr<FPhysicsEngine>		_physics_engine;
};

#endif /* ENGINE_FENGINE_H_ */
