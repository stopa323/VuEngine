/*
 * FActor.h
 *
 *  Created on: Feb 27, 2017
 *      Author: root
 */

#ifndef ENGINE_GAME_ENTITY_FACTOR_H_
#define ENGINE_GAME_ENTITY_FACTOR_H_

#include "UObject.h"

/**
 * Extends UObject functionality with additional features like timing or
 * replication; is able to have multiple components.
 */
class FActor: public UObject {
public:
	FActor();
	virtual ~FActor();
};

#endif /* ENGINE_GAME_ENTITY_FACTOR_H_ */
