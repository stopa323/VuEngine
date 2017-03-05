/*
 * FPhysicsEngine.h
 *
 *  Created on: Mar 4, 2017
 *      Author: root
 */

#ifndef ENGINE_PHYSICSENGINE_FPHYSICSENGINE_H_
#define ENGINE_PHYSICSENGINE_FPHYSICSENGINE_H_

#include "Timing/FTick.h"
#include <list>

class FPhysicsEngine {
public:
	FPhysicsEngine();
	virtual ~FPhysicsEngine();

	void UpdateTickables();

	void RegisterTickableObjects( FTick* tickableObject );
	void UnregisterTickableObjects( FTick* tickableObject );

private:
	// Todo: ouch! careful with that pointers
	std::list<FTick*> 		_tickable_objects;
};

#endif /* ENGINE_PHYSICSENGINE_FPHYSICSENGINE_H_ */
