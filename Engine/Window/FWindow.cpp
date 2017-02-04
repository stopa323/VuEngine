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
}

FWindow::~FWindow() {
	std::cout << "FWindow DTOR" << std::endl;
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
