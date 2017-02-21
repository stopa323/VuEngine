/*
 * FFPSMeter.cpp
 *
 *  Created on: Feb 21, 2017
 *      Author: tahion
 */

#include "FFPSMeter.h"
// Note: temporary
#include <iostream>

float FFPSMeter::_fps = 0;

FFPSMeter::FFPSMeter() { }

FFPSMeter::~FFPSMeter() { }

void FFPSMeter::UpdateFPS( const double& deltaTime ) {
	_frame_counter++;
	_timer += deltaTime;

	if ( _timer > _measurment_interval ) {
		FFPSMeter::_fps = _frame_counter / _timer;
		_frame_counter = 0;
		_timer = 0;
		// Note: temporary
		std::cout << "FPS: " << FFPSMeter::_fps << std::endl;
	}
}

double FFPSMeter::GetFPS() {
	return FFPSMeter::_fps;
}
