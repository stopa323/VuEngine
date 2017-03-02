/*
 * FPlayerController.h
 *
 *  Created on: Mar 2, 2017
 *      Author: root
 */

#ifndef ENGINE_GAME_CONTROLLER_FPLAYERCONTROLLER_H_
#define ENGINE_GAME_CONTROLLER_FPLAYERCONTROLLER_H_

#include "FController.h"

class FPlayerController: public FController {
public:
	FPlayerController();
	virtual ~FPlayerController();

	virtual void Tick() override;

private:
	typedef FController super;
};

#endif /* ENGINE_GAME_CONTROLLER_FPLAYERCONTROLLER_H_ */
