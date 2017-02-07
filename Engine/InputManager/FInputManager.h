/*
 * FInputManager.h
 *
 *  Created on: Feb 4, 2017
 *      Author: root
 */

#ifndef ENGINE_INPUTMANAGER_FINPUTMANAGER_H_
#define ENGINE_INPUTMANAGER_FINPUTMANAGER_H_

#include "input_mapping.h"
#include "../DummyPlayerController.h"
#include <xcb/xcb.h>
#include <functional>
#include <unordered_map>

typedef std::function<void(DummyPlayerController&)> 		ControllerFunctionPtr;
typedef std::unordered_map<uint8_t, ControllerFunctionPtr> 	MouseEventMap;

class FInputManager {
public:
	FInputManager( xcb_connection_t* xConnection );
	virtual ~FInputManager();

	void ProcessInput();
	void BindAction(EMouseEvent event,
					DummyPlayerController *controllerPtr,
					std::function<void(DummyPlayerController&)> functionPtr);

private:
	EMouseEvent getMouseButtonPressEvent();
	EMouseEvent getMouseButtonReleaseEvent();

	void onEventTriggered( EMouseEvent event );

	DummyPlayerController*		_controller_context		= nullptr;
	MouseEventMap				_mouse_event_map;

	xcb_connection_t*			_connection				= nullptr;
	xcb_generic_event_t*		_input_event			= nullptr;
};

#endif /* ENGINE_INPUTMANAGER_FINPUTMANAGER_H_ */
