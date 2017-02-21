/*
 * FEngineLoop.cpp
 *
 *  Created on: Feb 4, 2017
 *      Author: root
 */

#include "FEngineLoop.h"
#include <iostream>


FEngineLoop::FEngineLoop( std::shared_ptr<FInputManager> inputManager,
		std::shared_ptr<FSimpleRenderer> renderer,
		std::shared_ptr<FChrono> chrono ) :
	_input_manager( inputManager ),
	_renderer( renderer ),
	_chrono( chrono )
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
		_chrono->UpdateTime();

		/** Render graphics **/
		_renderer->RenderFrame();
	}
}
