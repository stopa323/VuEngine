/*
 * FController.cpp
 *
 *  Created on: Mar 2, 2017
 *      Author: root
 */

#include "FController.h"


FController::FController() { }

FController::~FController() { }

void FController::Tick() { }

void FController::Possess( FPawn* pawn ) {
	if ( pawn->IsPossesed ) return; // Todo: handle such situation

	_possessed_pawn = pawn;
	_possessed_pawn->IsPossesed = true;
}
