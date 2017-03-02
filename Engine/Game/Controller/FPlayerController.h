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

	void Event_InputAxisHorizontal( void* );
	void Event_InputAxisVertical( void* );

private:
	typedef FController super;

	void updateMovement();

	glm::vec3 		_move_vector;
	float			_move_speed;
};

#endif /* ENGINE_GAME_CONTROLLER_FPLAYERCONTROLLER_H_ */
