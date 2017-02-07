/*
 * DummyPlayerController.cpp
 *
 *  Created on: Feb 4, 2017
 *      Author: root
 */

#include "DummyPlayerController.h"
#include <iostream>

DummyPlayerController::DummyPlayerController() {}

DummyPlayerController::~DummyPlayerController() {}

void DummyPlayerController::Leszke() {
	std::cout << "nie wylaczajcie reaktora, wytrzyma" << std::endl;
}

void DummyPlayerController::Doniesiesz() {
	std::cout << "A ja mu wtedy na to" << std::endl;
}
