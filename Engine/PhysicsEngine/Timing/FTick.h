/*
 * FTick.h
 *
 *  Created on: Mar 1, 2017
 *      Author: root
 */

#ifndef ENGINE_PHYSICSENGINE_TIMING_FTICK_H_
#define ENGINE_PHYSICSENGINE_TIMING_FTICK_H_

class FTick {
public:
	FTick();
	virtual ~FTick();

	virtual void Tick() = 0;

	bool IsTicking;
};

#endif /* ENGINE_PHYSICSENGINE_TIMING_FTICK_H_ */
