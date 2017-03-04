/*
 * FActor.h
 *
 *  Created on: Feb 27, 2017
 *      Author: root
 */

#ifndef ENGINE_GAME_ENTITY_FACTOR_H_
#define ENGINE_GAME_ENTITY_FACTOR_H_

#include "../../PhysicsEngine/Timing/FTick.h"
#include "UObject.h"

/**
 * Basic object that can be placed in the scene. Extends UObject functionality
 * with additional features like timing or replication; is able to have multiple
 * components.
 */
class FActor: public UObject, public FTick {
public:
	FActor();
	virtual ~FActor();

	virtual void Tick() override;
};

#endif /* ENGINE_GAME_ENTITY_FACTOR_H_ */
