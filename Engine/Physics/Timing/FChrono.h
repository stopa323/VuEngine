/*
 * FChrono.h
 *
 *  Created on: Feb 21, 2017
 *      Author: tahion
 */

#ifndef ENGINE_PHYSICS_TIMING_FCHRONO_H_
#define ENGINE_PHYSICS_TIMING_FCHRONO_H_

#include <chrono>

typedef std::chrono::time_point<std::chrono::steady_clock> TTimePoint;


class FChrono {
public:
	// Todo: This doesn't work as intended, object should be initialized once
	// (inside Engine/EngineLoop) and only this instance should be able to call
	// UpdateTime()
	FChrono();
	virtual ~FChrono();

	void UpdateTime();
	static double DeltaTime();

private:
	TTimePoint				_current_frame_time;
	TTimePoint				_previous_frame_time;
	static double			_delta_time;

};

#endif /* ENGINE_PHYSICS_TIMING_FCHRONO_H_ */
