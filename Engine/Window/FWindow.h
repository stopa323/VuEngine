/*
 * FWindow.h
 *
 *  Created on: Feb 4, 2017
 *      Author: root
 */

#ifndef ENGINE_WINDOW_FWINDOW_H_
#define ENGINE_WINDOW_FWINDOW_H_

#include <xcb/xcb.h>


class FWindow {
public:
	FWindow( uint16_t width, uint16_t height );
	virtual ~FWindow();

	/** Getters/Setters **/
	const uint16_t& GetWidth() const;
	const uint16_t& GetHeight() const;
	// Todo: return reference
	xcb_window_t GetWindow() const;
	xcb_connection_t* GetConnection() const;

private:
	// Todo: smart pointers?
	xcb_connection_t*			_connection			= nullptr;
	xcb_window_t				_window				= 0;
	xcb_screen_t*				_screen				= nullptr;

	const uint16_t				_width				= 0;
	const uint16_t				_height				= 0;
};

#endif /* ENGINE_WINDOW_FWINDOW_H_ */
