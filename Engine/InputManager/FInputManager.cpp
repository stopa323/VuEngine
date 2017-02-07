/*
 * FInputManager.cpp
 *
 *  Created on: Feb 4, 2017
 *      Author: root
 */

#include "FInputManager.h"
#include <iostream>


FInputManager::FInputManager( xcb_connection_t* xConnection ) :
	_connection( xConnection )
{
	std::cout << "FInputManager CTOR" << std::endl;
}

FInputManager::~FInputManager() {
	std::cout << "FInputManager DTOR" << std::endl;
}

void FInputManager::ProcessInput() {
	// Todo: handle all input in one call (while loop)
	_input_event = xcb_poll_for_event( _connection );
	if ( nullptr == _input_event ) {
		free( _input_event );
		return;
	}

	EMouseEvent mouse_event = EMouseEvent::UNKNOWN;

	/* Switch on event type */
	switch ( _input_event->response_type & ~0x80 ) {
	case XCB_BUTTON_PRESS: {
		mouse_event = getMouseButtonPressEvent();
	} break;
	case XCB_BUTTON_RELEASE: {
		mouse_event = getMouseButtonReleaseEvent();
	} break;
	case XCB_MOTION_NOTIFY: {
		std::cout << "XCB_MOTION_NOTIFY" << std::endl;
	} break;
	case XCB_KEY_PRESS: {
		std::cout << "XCB_KEY_PRESS" << std::endl;
	} break;
	case XCB_KEY_RELEASE: {
		std::cout << "XCB_KEY_RELEASE" << std::endl;
	} break;
	}

	if ( EMouseEvent::UNKNOWN != mouse_event)
		onEventTriggered( mouse_event );

	/* Free generic event */
	free( _input_event );
}

void FInputManager::BindAction(EMouseEvent event,
							   DummyPlayerController *controllerPtr,
							   std::function<void(DummyPlayerController&)> functionPtr) {
	auto event_id = (uint8_t) event;
	// Note: this may cause problems in the future since one context is supported for now
	// and any subsequent binding overrides this value
	_controller_context = controllerPtr;
	_mouse_event_map[event_id] = functionPtr;
}

void FInputManager::onEventTriggered( EMouseEvent event ) {
	if ( nullptr == _controller_context ) {
		std::cout << "ERROR: Controller contex NULL" << std::endl;
		return;
	}

	auto event_id = (uint8_t) event;
	MouseEventMap::const_iterator iter = _mouse_event_map.find( event_id );
	if ( _mouse_event_map.end() != iter ) {
		ControllerFunctionPtr action_ptr = iter->second;
		action_ptr( *_controller_context );
	}
}

EMouseEvent FInputManager::getMouseButtonPressEvent() {
	xcb_button_press_event_t* press_event = (xcb_button_press_event_t*) _input_event;
	uint16_t event_modifiers = press_event->state;

	/* Substract unused modifiers */
	event_modifiers &= (MOUSE_BUTTON_MOD_CAPSLOCK^0xffff);
	event_modifiers &= (MOUSE_BUTTON_MOD_NUMLOCK^0xffff);

	if ( (MOUSE_BUTTON_MOD_SHIFT) == event_modifiers ) {
		if ( MOUSE_BUTTON_LEFT 			== press_event->detail ) return EMouseEvent::LMB_SHIFT_PRESS;
		if ( MOUSE_BUTTON_MIDDLE 		== press_event->detail ) return EMouseEvent::MMB_SHIFT_PRESS;
		if ( MOUSE_BUTTON_RIGHT 		== press_event->detail ) return EMouseEvent::RMB_SHIFT_PRESS;
		if ( MOUSE_BUTTON_WHEEL_UP 		== press_event->detail ) return EMouseEvent::WHEEL_UP_SHIFT;
		if ( MOUSE_BUTTON_WHEEL_DOWN 	== press_event->detail ) return EMouseEvent::WHEEL_DOWN_SHIFT;
	}

	if ( (MOUSE_BUTTON_MOD_CTRL) == event_modifiers ) {
		if ( MOUSE_BUTTON_LEFT 			== press_event->detail ) return EMouseEvent::LMB_CTRL_PRESS;
		if ( MOUSE_BUTTON_MIDDLE 		== press_event->detail ) return EMouseEvent::MMB_CTRL_PRESS;
		if ( MOUSE_BUTTON_RIGHT 		== press_event->detail ) return EMouseEvent::RMB_CTRL_PRESS;
		if ( MOUSE_BUTTON_WHEEL_UP 		== press_event->detail ) return EMouseEvent::WHEEL_UP_CTRL;
		if ( MOUSE_BUTTON_WHEEL_DOWN 	== press_event->detail ) return EMouseEvent::WHEEL_DOWN_CTRL;
	}

	if ( (MOUSE_BUTTON_MOD_LALT) == event_modifiers ) {
		// Note: its not working, window does not handle this event
		std::cout << "NOT IMPLEMENTED" << std::endl;
	}

	if ( (MOUSE_BUTTON_MOD_SHIFT_CTRL) == event_modifiers ) {
		if ( MOUSE_BUTTON_LEFT 			== press_event->detail ) return EMouseEvent::LMB_SHIFT_CTRL_PRESS;
		if ( MOUSE_BUTTON_MIDDLE 		== press_event->detail ) return EMouseEvent::MMB_SHIFT_CTRL_PRESS;
		if ( MOUSE_BUTTON_RIGHT 		== press_event->detail ) return EMouseEvent::RMB_SHIFT_CTRL_PRESS;
		if ( MOUSE_BUTTON_WHEEL_UP 		== press_event->detail ) return EMouseEvent::WHEEL_UP;
		if ( MOUSE_BUTTON_WHEEL_DOWN 	== press_event->detail ) return EMouseEvent::WHEEL_DOWN;
	}

	if ( (MOUSE_BUTTON_MOD_SHIFT_LALT) == event_modifiers ) {
		if ( MOUSE_BUTTON_LEFT 			== press_event->detail ) return EMouseEvent::LMB_SHIFT_LALT_PRESS;
		if ( MOUSE_BUTTON_MIDDLE 		== press_event->detail ) return EMouseEvent::MMB_SHIFT_LALT_PRESS;
		if ( MOUSE_BUTTON_RIGHT 		== press_event->detail ) return EMouseEvent::RMB_SHIFT_LALT_PRESS;
		if ( MOUSE_BUTTON_WHEEL_UP 		== press_event->detail ) return EMouseEvent::WHEEL_UP;
		if ( MOUSE_BUTTON_WHEEL_DOWN 	== press_event->detail ) return EMouseEvent::WHEEL_DOWN;
	}

	if ( (MOUSE_BUTTON_MOD_CTRL_LALT) == event_modifiers ) {
		if ( MOUSE_BUTTON_LEFT 			== press_event->detail ) return EMouseEvent::LMB_CTRL_LALT_PRESS;
		if ( MOUSE_BUTTON_MIDDLE 		== press_event->detail ) return EMouseEvent::MMB_CTRL_LALT_PRESS;
		if ( MOUSE_BUTTON_RIGHT 		== press_event->detail ) return EMouseEvent::RMB_CTRL_LALT_PRESS;
		if ( MOUSE_BUTTON_WHEEL_UP 		== press_event->detail ) return EMouseEvent::WHEEL_UP;
		if ( MOUSE_BUTTON_WHEEL_DOWN 	== press_event->detail ) return EMouseEvent::WHEEL_DOWN;
	}

	if ( (MOUSE_BUTTON_MOD_SHIFT_CTRL_LALT) == event_modifiers ) {
		if ( MOUSE_BUTTON_LEFT 			== press_event->detail ) return EMouseEvent::LMB_SHIFT_CTRL_LALT_PRESS;
		if ( MOUSE_BUTTON_MIDDLE 		== press_event->detail ) return EMouseEvent::MMB_SHIFT_CTRL_LALT_PRESS;
		if ( MOUSE_BUTTON_RIGHT 		== press_event->detail ) return EMouseEvent::RMB_SHIFT_CTRL_LALT_PRESS;
		if ( MOUSE_BUTTON_WHEEL_UP 		== press_event->detail ) return EMouseEvent::WHEEL_UP;
		if ( MOUSE_BUTTON_WHEEL_DOWN 	== press_event->detail ) return EMouseEvent::WHEEL_DOWN;
	}

	/* Treat any other combination as no modifiers */
	if ( MOUSE_BUTTON_LEFT 			== press_event->detail ) return EMouseEvent::LMB_PRESS;
	if ( MOUSE_BUTTON_MIDDLE 		== press_event->detail ) return EMouseEvent::MMB_PRESS;
	if ( MOUSE_BUTTON_RIGHT 		== press_event->detail ) return EMouseEvent::RMB_PRESS;
	if ( MOUSE_BUTTON_WHEEL_UP 		== press_event->detail ) return EMouseEvent::WHEEL_UP;
	if ( MOUSE_BUTTON_WHEEL_DOWN 	== press_event->detail ) return EMouseEvent::WHEEL_DOWN;

	return EMouseEvent::UNKNOWN;
}

EMouseEvent FInputManager::getMouseButtonReleaseEvent() {
	xcb_button_release_event_t* press_event = (xcb_button_release_event_t*) _input_event;

	if ( MOUSE_BUTTON_LEFT 			== press_event->detail ) return EMouseEvent::LMB_RELEASE;
	if ( MOUSE_BUTTON_MIDDLE 		== press_event->detail ) return EMouseEvent::MMB_RELEASE;
	if ( MOUSE_BUTTON_RIGHT 		== press_event->detail ) return EMouseEvent::RMB_RELEASE;
	if ( MOUSE_BUTTON_WHEEL_UP 		== press_event->detail ) return EMouseEvent::WHEEL_UP;
	if ( MOUSE_BUTTON_WHEEL_DOWN 	== press_event->detail ) return EMouseEvent::WHEEL_DOWN;

	return EMouseEvent::UNKNOWN;
}
