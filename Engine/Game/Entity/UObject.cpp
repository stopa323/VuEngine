/*
 * UObject.cpp
 *
 *  Created on: Feb 27, 2017
 *      Author: root
 */

#include "UObject.h"

UObject::UObject() :
	_transform( STransform() )
{ }

UObject::~UObject() { }

const STransform& UObject::GetTransform() const {
	return _transform;
}
