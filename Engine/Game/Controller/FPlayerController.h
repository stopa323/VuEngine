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

	// Todo: Consider binding this events (movement is common) directly in
	// InputManager; here we would receive simple events with direction vector.
	void Event_InputMoveForward();
	void Event_InputMoveBackward();
	void Event_InputMoveRight();
	void Event_InputMoveLeft();

	void Event_RELEASE_InputMoveForward();
	void Event_RELEASE_InputMoveBackward();
	void Event_RELEASE_InputMoveRight();
	void Event_RELEASE_InputMoveLeft();

private:
	typedef FController super;

	void updateMovement();

	glm::vec3 		_move_vector;
	float			_move_speed;
};

#endif /* ENGINE_GAME_CONTROLLER_FPLAYERCONTROLLER_H_ */
