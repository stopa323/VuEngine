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
	std::cout << "FEngine CTOR" << std::endl;
}

FEngine::~FEngine() {
	std::cout << "FEngine DTOR" << std::endl;
}

void FEngine::Initialize() {
	if ( EEngineResult::FAIL == createWindow() ) {
		throw std::runtime_error( "FEngine: Engine initialization failed." );
	}

	if ( EEngineResult::FAIL == createInputManager() ) {
		throw std::runtime_error( "FEngine: Engine initialization failed." );
	}

	if ( EEngineResult::FAIL == createEngineLoop() ) {
		throw std::runtime_error( "FEngine: Engine initialization failed." );
	}
}

EEngineResult FEngine::createWindow() {
	try {
		_window = std::shared_ptr<FWindow>(new FWindow( 400, 300 ));
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

EEngineResult FEngine::createInputManager() {
	try {
		_input_manager = std::shared_ptr<FInputManager>(
		new FInputManager(_window->GetConnection()) );
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

EEngineResult FEngine::createEngineLoop() {
	try {
		_engine_loop = std::shared_ptr<FEngineLoop>(
		new FEngineLoop( _input_manager ));
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

std::shared_ptr<FWindow> FEngine::GetWindow() const {
	return _window;
}

std::shared_ptr<FInputManager> FEngine::GetInputManager() const {
	return _input_manager;
}

std::shared_ptr<FEngineLoop> FEngine::GetEngineLoop() const {
	return _engine_loop;
}
