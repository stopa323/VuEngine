/*
 * FEngineLoop.h
 *
 *  Created on: Feb 4, 2017
 *      Author: root
 */

#ifndef ENGINE_FENGINELOOP_H_
#define ENGINE_FENGINELOOP_H_

#include "InputManager/FInputManager.h"
#include <cstdint>
#include <memory>


enum class EEngineLoopState : uint8_t {
	INIT					= 0,
	RUNNING					= 1,
	DISMANTLING				= 2
};

class FEngineLoop {
public:
	FEngineLoop( std::shared_ptr<FInputManager> inputManager );
	virtual ~FEngineLoop();

	void Run();

private:
	// Todo: consider weak ptr
	std::shared_ptr<FInputManager>	_input_manager;

	EEngineLoopState 				_state 				= EEngineLoopState::INIT;
};

#endif /* ENGINE_FENGINELOOP_H_ */
