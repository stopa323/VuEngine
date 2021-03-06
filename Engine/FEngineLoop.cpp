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
		std::shared_ptr<FChrono> chrono,
		std::shared_ptr<FPhysicsEngine>	physics_engine) :
	_input_manager( inputManager ),
	_renderer( renderer ),
	_chrono( chrono ),
	_physics_engine( physics_engine )
{
	std::cout << "FEngineLoop CTOR" << std::endl;
	_fps_meter = std::shared_ptr<FFPSMeter>( new FFPSMeter() );
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
		_fps_meter->UpdateFPS( FChrono::DeltaTime() );

		_physics_engine->UpdateTickables();

		//_renderer->ubo.model_mtx =
		// Note: commenting this out increases FPS from ~1k to ~4k :(
		_renderer->UpdateUniformBuffer();

		/** Render graphics **/
		_renderer->RenderFrame();
	}
}
