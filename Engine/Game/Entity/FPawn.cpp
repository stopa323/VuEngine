/*
 * FPawn.cpp
 *
 *  Created on: Mar 1, 2017
 *      Author: root
 */

#include "FPawn.h"

FPawn::FPawn() { }

FPawn::~FPawn() { }

void FPawn::Move( const glm::vec3 moveVector ) {
	_transform.Translate( moveVector );
}
