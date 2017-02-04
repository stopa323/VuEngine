/*
 * FInputManager.h
 *
 *  Created on: Feb 4, 2017
 *      Author: root
 */

#ifndef ENGINE_INPUTMANAGER_FINPUTMANAGER_H_
#define ENGINE_INPUTMANAGER_FINPUTMANAGER_H_

#include "input_mapping.h"
#include <xcb/xcb.h>


class FInputManager {
public:
	FInputManager( xcb_connection_t* xConnection );
	virtual ~FInputManager();

	void ProcessInput();

private:
	EMouseEvent getMouseButtonPressEvent();
	EMouseEvent getMouseButtonReleaseEvent();

	xcb_connection_t*			_connection				= nullptr;
	xcb_generic_event_t*		_input_event			= nullptr;
};

#endif /* ENGINE_INPUTMANAGER_FINPUTMANAGER_H_ */
