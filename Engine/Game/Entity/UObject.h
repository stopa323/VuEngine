/*
 * UObject.h
 *
 *  Created on: Feb 27, 2017
 *      Author: root
 */

#ifndef ENGINE_GAME_ENTITY_UOBJECT_H_
#define ENGINE_GAME_ENTITY_UOBJECT_H_

#include "STransform.h"

/**
 * Simple container for essential components.
 */
class UObject {
public:
	UObject();
	virtual ~UObject();

	const STransform& GetTransform() const;

protected:
	STransform 		_transform;
};

#endif /* ENGINE_GAME_ENTITY_UOBJECT_H_ */
