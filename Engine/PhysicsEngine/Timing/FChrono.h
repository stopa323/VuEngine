/*
 * FChrono.h
 *
 *  Created on: Feb 21, 2017
 *      Author: tahion
 */

#ifndef ENGINE_PHYSICSENGINE_TIMING_FCHRONO_H_
#define ENGINE_PHYSICSENGINE_TIMING_FCHRONO_H_

#include <chrono>

typedef std::chrono::time_point<std::chrono::steady_clock> TTimePoint;


class FChrono {
public:
	// Todo: This doesn't work as intended, object should be initialized once
	// (inside Engine/EngineLoop) and only this instance should be able to call
	// UpdateTime()
	// Todo v2: In fact, every tickable object will be updated by one system, so
	// Tick() function can take additional deltaTime parameter provided by this
	// system. That solution would allow to store Chrono object in one place
	// (no static methods would be needed)
	FChrono();
	virtual ~FChrono();

	void UpdateTime();
	static double DeltaTime();

private:
	TTimePoint				_current_frame_time;
	TTimePoint				_previous_frame_time;
	static double			_delta_time;

};

#endif /* ENGINE_PHYSICSENGINE_TIMING_FCHRONO_H_ */
