/*
 * FPhysicsEngine.cpp
 *
 *  Created on: Mar 4, 2017
 *      Author: root
 */

#include "FPhysicsEngine.h"

FPhysicsEngine::FPhysicsEngine() { }

FPhysicsEngine::~FPhysicsEngine() { }

void FPhysicsEngine::UpdateTickables() {
	for ( FTick* tickable : _tickable_objects ) {
		tickable->Tick();
	}
}

void FPhysicsEngine::RegisterTickableObjects( FTick* tickableObject ) {
	if ( nullptr == tickableObject ) return; // Todo: LOGS!

	_tickable_objects.push_back( tickableObject );
}

void FPhysicsEngine::UnregisterTickableObjects( FTick* tickableObject ) {
	if ( nullptr == tickableObject ) return; // Todo: LOGS!

	_tickable_objects.remove( tickableObject );
}
