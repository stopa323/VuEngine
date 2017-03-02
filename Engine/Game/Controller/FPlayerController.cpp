/*
 * FPlayerController.cpp
 *
 *  Created on: Mar 2, 2017
 *      Author: root
 */

#include "FPlayerController.h"
#include "../../Physics/Timing/FChrono.h"

FPlayerController::FPlayerController() :
	_move_vector( glm::vec3(0, 0, 0) ),
	_move_speed( 10.0f )
{ }

FPlayerController::~FPlayerController() { }

void FPlayerController::Tick() {
	super::Tick();

	// Todo: should be replaced with sth like IsAbleToMove
	if ( nullptr != _possessed_pawn && ( _move_vector.x != 0 || _move_vector.y != 0
			|| _move_vector.z != 0) ) {
		updateMovement();
	}
}

void FPlayerController::Event_InputAxisHorizontal( void* data ) {
	int8_t* axis_data = static_cast<int8_t*>( data );

	if ( nullptr == axis_data ) return;

	_move_vector.x = *axis_data;
}

void FPlayerController::Event_InputAxisVertical( void* data ) {
	int8_t* axis_data = static_cast<int8_t*>( data );

	if ( nullptr == axis_data ) return;

	_move_vector.z = *axis_data;
}

void FPlayerController::updateMovement() {
	glm::vec3 direction_vector = glm::normalize( _move_vector );
	_possessed_pawn->Move( direction_vector * _move_speed * FChrono::DeltaTime() );
}
