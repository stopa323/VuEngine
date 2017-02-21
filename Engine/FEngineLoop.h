/*
 * FEngineLoop.h
 *
 *  Created on: Feb 4, 2017
 *      Author: root
 */

#ifndef ENGINE_FENGINELOOP_H_
#define ENGINE_FENGINELOOP_H_

#include "InputManager/FInputManager.h"
#include "Renderer/FSimpleRenderer.h"
#include "Physics/Timing/FChrono.h"
#include "Game/FFPSMeter.h"
#include <cstdint>
#include <memory>


enum class EEngineLoopState : uint8_t {
	INIT					= 0,
	RUNNING					= 1,
	DISMANTLING				= 2
};

class FEngineLoop {
public:
	FEngineLoop( std::shared_ptr<FInputManager> inputManager,
			std::shared_ptr<FSimpleRenderer> renderer,
			std::shared_ptr<FChrono> chrono );
	virtual ~FEngineLoop();

	void Run();

private:
	// Todo: consider weak ptr or reference
	std::shared_ptr<FInputManager>		_input_manager;
	std::shared_ptr<FSimpleRenderer>	_renderer;
	std::shared_ptr<FChrono>			_chrono;
	std::shared_ptr<FFPSMeter>			_fps_meter;

	EEngineLoopState 					_state 			= EEngineLoopState::INIT;
};

#endif /* ENGINE_FENGINELOOP_H_ */
