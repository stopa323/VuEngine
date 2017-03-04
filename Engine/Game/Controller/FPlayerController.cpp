/*
 * FPlayerController.cpp
 *
 *  Created on: Mar 2, 2017
 *      Author: root
 */

#include "FPlayerController.h"
#include "../../Physics/Timing/FChrono.h"
#include <iostream>

FPlayerController::FPlayerController() :
	_move_vector( glm::vec3(0, 0, 0) ),
	_move_speed( 10.0f )
{ }

FPlayerController::~FPlayerController() { }

void FPlayerController::Tick() {
	super::Tick();

	// Todo: should be replaced with sth like IsAbleToMove
	if ( nullptr != _possessed_pawn ) {
		updateMovement();
	}
}

void FPlayerController::Event_InputMoveForward() { _move_vector.z = 1.0f; }

void FPlayerController::Event_InputMoveBackward() { _move_vector.z = -1.0f; }

void FPlayerController::Event_InputMoveRight() { _move_vector.x = 1.0f; }

void FPlayerController::Event_InputMoveLeft() { _move_vector.x = -1.0f; }

void FPlayerController::updateMovement() {
	glm::vec3 direction_vector = glm::normalize( _move_vector );
	_possessed_pawn->Move( direction_vector * _move_speed * FChrono::DeltaTime() );
	_move_vector = glm::vec3( 0.0f );
}
