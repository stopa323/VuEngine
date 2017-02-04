/*
 * FInputManager.cpp
 *
 *  Created on: Feb 4, 2017
 *      Author: root
 */

#include "FInputManager.h"
#include <iostream>


FInputManager::FInputManager( xcb_connection_t* xConnection ) :
	_connection( xConnection )
{
	std::cout << "FInputManager CTOR" << std::endl;
}

FInputManager::~FInputManager() {
	std::cout << "FInputManager DTOR" << std::endl;
}

void FInputManager::ProcessInput() {

}

EMouseEvent FInputManager::getMouseButtonPressEvent() {
	return EMouseEvent::UNKNOWN;
}

EMouseEvent FInputManager::getMouseButtonReleaseEvent() {
	return EMouseEvent::UNKNOWN;
}
