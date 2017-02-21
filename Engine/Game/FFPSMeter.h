/*
 * FFPSMeter.h
 *
 *  Created on: Feb 21, 2017
 *      Author: tahion
 */

#ifndef ENGINE_GAME_FFPSMETER_H_
#define ENGINE_GAME_FFPSMETER_H_

#include <cstddef>

class FFPSMeter {
public:
	FFPSMeter();
	virtual ~FFPSMeter();

	void UpdateFPS( const double& deltaTime );
	static double GetFPS();

private:
	const double 		_measurment_interval		= 5;
	// Todo: need some class for Timers
	double				_timer						= 0;
	size_t				_frame_counter				= 0;

	static float 		_fps;
};

#endif /* ENGINE_GAME_FFPSMETER_H_ */
