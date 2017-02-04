/*
 * FWindow.cpp
 *
 *  Created on: Feb 4, 2017
 *      Author: root
 */

#include "FWindow.h"
#include <iostream>


FWindow::FWindow( uint16_t width, uint16_t height ) :
	_width( width ),
	_height( _height)
{
	std::cout << "FWindow CTOR" << std::endl;
	{
		/* Open the connection to the X server using DISPLAY env variable */
		_connection = xcb_connect( nullptr, nullptr );

		/* Error handling */
		auto result = xcb_connection_has_error( _connection );
		if ( result > 0 ) {
			switch ( result ) {
			case XCB_CONN_ERROR: {
				xcb_disconnect( _connection );
				throw std::runtime_error( "FWindow ERROR: Connection failed due to some stream error." );
			} break;
			case XCB_CONN_CLOSED_EXT_NOTSUPPORTED: {
				xcb_disconnect( _connection );
				throw std::runtime_error( "FWindow ERROR: Extension not supported." );
			} break;
			case XCB_CONN_CLOSED_MEM_INSUFFICIENT: {
				xcb_disconnect( _connection );
				throw std::runtime_error( "FWindow ERROR: Insufficient memory." );
			} break;
			case XCB_CONN_CLOSED_REQ_LEN_EXCEED: {
				xcb_disconnect( _connection );
				throw std::runtime_error( "FWindow ERROR: Request length exceeded." );
			} break;
			case XCB_CONN_CLOSED_PARSE_ERR: {
				xcb_disconnect( _connection );
				throw std::runtime_error( "FWindow ERROR: Error during parsing display string." );
			} break;
			case XCB_CONN_CLOSED_INVALID_SCREEN: {
				xcb_disconnect( _connection );
				throw std::runtime_error( "FWindow ERROR: Invalid string." );
			} break;
			default: {
				xcb_disconnect( _connection );
				throw std::runtime_error( "FWindow ERROR: Unknown error." );
			}
			}
		}
	}

	{
		/* Get the first screen */
		const xcb_setup_t *setup = xcb_get_setup( _connection );

		if ( nullptr == setup ) {
			xcb_disconnect( _connection );
			throw std::runtime_error( "FWindow ERROR: Could not access setup returned by the server." );
		}

		xcb_screen_iterator_t iter = xcb_setup_roots_iterator (setup);
		_screen = iter.data;
	}

	{
		/* Mask for event registering */
		// Todo: move outside and use xcb_change_window_attributes
		uint32_t mask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
		uint32_t values[2];
		values[0] = _screen->white_pixel;
		values[1] = XCB_EVENT_MASK_BUTTON_PRESS		| XCB_EVENT_MASK_BUTTON_RELEASE |
					XCB_EVENT_MASK_POINTER_MOTION	| XCB_EVENT_MASK_KEY_PRESS		|
					XCB_EVENT_MASK_KEY_RELEASE;

		/* Create the window */
		// Todo: add come error handling
		_window = xcb_generate_id( _connection );
		xcb_create_window( _connection,						/* Connection */
						   XCB_COPY_FROM_PARENT,			/* Depth */
						   _window,							/* Window ID */
						   _screen->root,					/* Parent window */
						   0, 0,							/* Anchor position */
						   _width,							/* Width */
						   _height,							/* Height */
						   10,								/* Border width */
						   XCB_WINDOW_CLASS_INPUT_OUTPUT,	/* Class */
						   _screen->root_visual,			/* Visual */
						   mask, values);					/* Masks */
	}

	/* Map window on the screen */
	// Todo: add come error handling
	xcb_map_window( _connection, _window );

	/* Make sure commands are sent, so the window is shown */
	// Todo: add come error handling
	xcb_flush( _connection );
}

FWindow::~FWindow() {
	std::cout << "FWindow DTOR" << std::endl;

	xcb_disconnect( _connection );

	_connection 			= nullptr;
	_window					= 0;
	_screen					= nullptr;
}

const uint16_t& FWindow::GetWidth() const {
	return _width;
}

const uint16_t& FWindow::GetHeight() const {
	return _height;
}

xcb_window_t FWindow::GetWindow() const {
	return _window;
}

xcb_connection_t* FWindow::GetConnection() const {
	return _connection;
}
