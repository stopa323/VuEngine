/*
 * FController.h
 *
 *  Created on: Mar 2, 2017
 *      Author: root
 */

#ifndef ENGINE_GAME_CONTROLLER_FCONTROLLER_H_
#define ENGINE_GAME_CONTROLLER_FCONTROLLER_H_

#include "../../Physics/Timing/FTick.h"
#include "../Entity/FPawn.h"

class FController : public FTick {
public:
	FController();
	virtual ~FController();

	virtual void Tick() override;

	void Possess( FPawn* pawn );

protected:
	FPawn*		_possessed_pawn			= nullptr;
};

#endif /* ENGINE_GAME_CONTROLLER_FCONTROLLER_H_ */
