/*
 * FInputManager.h
 *
 *  Created on: Feb 4, 2017
 *      Author: root
 */

#ifndef ENGINE_INPUTMANAGER_FINPUTMANAGER_H_
#define ENGINE_INPUTMANAGER_FINPUTMANAGER_H_

#include "input_mapping.h"
#include "../Game/Controller/FPlayerController.h"
#include <xcb/xcb.h>
#include <functional>
#include <unordered_map>

typedef std::function<void(FPlayerController&)> 			ControllerFunctionPtr;
typedef std::unordered_map<uint8_t, ControllerFunctionPtr> 	MouseEventMap;

typedef std::unordered_map<uint8_t, ControllerFunctionPtr>	ModifierMap;
typedef std::unordered_map<uint8_t, ModifierMap>			KeyboardEventMap;

class FInputManager {
public:
	FInputManager( xcb_connection_t* xConnection );
	virtual ~FInputManager();

	void ProcessInput();
	void BindAction(EMouseEvent event, FPlayerController *controllerPtr,
			ControllerFunctionPtr functionPtr);
	void BindAction(EKeyboardKey key, EInputModifier modifier, EInputType type,
			FPlayerController *controllerPtr, ControllerFunctionPtr action);

private:
	EMouseEvent getMouseButtonPressEvent();
	EMouseEvent getMouseButtonReleaseEvent();

	SKeyboardEvent getKeyboardKeyPressEvent();
	SKeyboardEvent getKeyboardKeyReleaseEvent();

	void onEventTriggered( EMouseEvent event );
	void onEventTriggered( SKeyboardEvent event );

	FPlayerController*			_controller_context		= nullptr;
	MouseEventMap				_mouse_event_map;
	KeyboardEventMap			_keyboard_press_map;
	KeyboardEventMap			_keyboard_release_map;

	xcb_connection_t*			_connection				= nullptr;
	xcb_generic_event_t*		_input_event			= nullptr;
};

#endif /* ENGINE_INPUTMANAGER_FINPUTMANAGER_H_ */
