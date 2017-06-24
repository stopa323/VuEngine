/*
 * FEngine.cpp
 *
 *  Created on: Feb 4, 2017
 *      Author: root
 */

#include "FEngine.h"
#include <exception>
#include <iostream>


FEngine::FEngine() {
	/* Create context */
	try {
		std::shared_ptr<FWindow>			window;
		std::shared_ptr<FInputManager>		input_manager;
		std::shared_ptr<FSimpleRenderer>	render_engine;
		std::shared_ptr<FPhysicsEngine>		physics_engine;

		window = std::shared_ptr<FWindow>( new FWindow(400, 300) );

		input_manager = std::shared_ptr<FInputManager>(
				new FInputManager(window->GetConnection()) );

		render_engine = std::shared_ptr<FSimpleRenderer>(
				new FSimpleRenderer(*window) );

		physics_engine = std::shared_ptr<FPhysicsEngine>(
				new FPhysicsEngine() );

		_Context = {
			.Window			= window,
			.InputManager 	= input_manager,
			.RenderEngine	= render_engine,
			.PhysicsEngine	= physics_engine
		};
	}
	catch (std::runtime_error& err) {
		std::cout << "Engine creation failed. " << err.what() << std::endl;
	}
}

FEngine::~FEngine() { }

void FEngine::Initialize() {

	if ( EEngineResult::FAIL == createRenderer() ) {
		throw std::runtime_error( "FEngine: Engine initialization failed." );
	}

	if ( EEngineResult::FAIL == createPhysicsEngine() ) {
		throw std::runtime_error( "FEngine: Engine initialization failed." );
	}

	if ( EEngineResult::FAIL == createEngineLoop() ) {
		throw std::runtime_error( "FEngine: Engine initialization failed." );
	}
}

EEngineResult FEngine::createEngineLoop() {
	try {
		_engine_loop = std::shared_ptr<FEngineLoop>(
				new FEngineLoop( _input_manager, _renderer,
						_physics_engine ) );
	}
	catch ( std::runtime_error& err ) {
		std::cout << err.what() << std::endl;
		return EEngineResult::FAIL;
	}
	catch ( std::bad_alloc& err ) {
		std::cout << err.what() << std::endl;
		return EEngineResult::FAIL;
	}

	return EEngineResult::SUCCESS;
}

EEngineResult FEngine::createRenderer() {
	try {
		_renderer = std::shared_ptr<FSimpleRenderer>(
				new FSimpleRenderer( *_window ));
	}
	catch ( std::runtime_error& err ) {
		std::cout << err.what() << std::endl;
		return EEngineResult::FAIL;
	}

	return EEngineResult::SUCCESS;
}

EEngineResult FEngine::createPhysicsEngine() {
	try {
		_physics_engine = std::shared_ptr<FPhysicsEngine>( new FPhysicsEngine() );
	}
	catch ( std::runtime_error& err ) {
		std::cout << err.what() << std::endl;
		return EEngineResult::FAIL;
	}

	return EEngineResult::SUCCESS;
}

const SEngineContext& FEngine::GetContext() const {
	return *_Context;
}
