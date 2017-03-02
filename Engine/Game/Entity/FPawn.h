/*
 * FPawn.h
 *
 *  Created on: Mar 1, 2017
 *      Author: root
 */

#ifndef ENGINE_GAME_ENTITY_FPAWN_H_
#define ENGINE_GAME_ENTITY_FPAWN_H_

#include "FActor.h"

/**
 * Object possessed and orchestrated by Controller
 */
class FPawn: public FActor {
public:
	FPawn();
	virtual ~FPawn();

	void Move( const glm::vec3 moveVector );

	bool 			IsPossesed		= false;

};

#endif /* ENGINE_GAME_ENTITY_FPAWN_H_ */
