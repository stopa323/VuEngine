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
	std::cout << "FEngine_cpy CTOR" << std::endl;
}

FEngine::~FEngine() {
	std::cout << "FEngine_cpy DTOR" << std::endl;
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

EEngineResult FEngine::createEngineLoop() {
	return EEngineResult::SUCCESS;
}

EEngineResult FEngine::createInputManager() {
	return EEngineResult::SUCCESS;
}
