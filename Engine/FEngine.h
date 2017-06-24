/*
 * FEngine.h
 *
 *  Created on: Feb 4, 2017
 *      Author: root
 */

#ifndef ENGINE_FENGINE_H_
#define ENGINE_FENGINE_H_

#include "engine_common.h"
#include "FEngineLoop.h"


enum class EEngineResult : uint8_t {
	SUCCESS						= 0,
	FAIL						= 1
};


class FEngine {
public:
	FEngine();
	virtual ~FEngine();

	void Initialize();

	/** Getters/Setters **/
	const SEngineContext& GetContext() const;

private:
	// Todo: consider some Factory
	EEngineResult createEngineLoop();
	EEngineResult createRenderer();
	EEngineResult createPhysicsEngine();

	// Todo: redesign necessary - whats the point initializing elements
	FEngineLoop						_EngineLoop;
	SEngineContext					_Context;
};

#endif /* ENGINE_FENGINE_H_ */
