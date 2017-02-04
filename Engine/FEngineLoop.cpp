/*
 * FEngineLoop.cpp
 *
 *  Created on: Feb 4, 2017
 *      Author: root
 */

#include "FEngineLoop.h"
#include <iostream>


FEngineLoop::FEngineLoop( std::shared_ptr<FInputManager> inputManager ) :
	_input_manager( inputManager )
{
	std::cout << "FEngineLoop CTOR" << std::endl;
}

FEngineLoop::~FEngineLoop() {
	std::cout << "FEngineLoop DTOR" << std::endl;
}

void FEngineLoop::Run() {
	_state = EEngineLoopState::RUNNING;

	while ( EEngineLoopState::RUNNING == _state ) {
		/** Process input **/
		_input_manager->ProcessInput();

		/** Update game state **/

		/** Render graphics **/
	}
}
