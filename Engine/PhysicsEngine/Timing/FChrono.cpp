/*
 * FChrono.cpp
 *
 *  Created on: Feb 21, 2017
 *      Author: tahion
 */

#include "../../PhysicsEngine/Timing/FChrono.h"

double FChrono::_delta_time = 0;


FChrono::FChrono() {
	_current_frame_time = std::chrono::steady_clock::now();
	_previous_frame_time = std::chrono::steady_clock::now();
}

FChrono::~FChrono() { }

void FChrono::UpdateTime() {
	_current_frame_time = std::chrono::steady_clock::now();

	FChrono::_delta_time = std::chrono::duration_cast<std::chrono::duration<double>>
			(_current_frame_time - _previous_frame_time).count();

	_previous_frame_time = _current_frame_time;
}

double FChrono::DeltaTime() {
	return FChrono::_delta_time;
}
