/*
 * STransform.cpp
 *
 *  Created on: Feb 27, 2017
 *      Author: root
 */

#include "STransform.h"


const glm::vec3 STransform::GetPosition() const {
	return glm::vec3( _position_mtx[3][0], _position_mtx[3][1], _position_mtx[3][2]);
}

//const glm::vec3 STransform::GetWorldPosition() const { }

void STransform::Translate( glm::vec3 translateVector ) {
	_position_mtx = glm::translate( _position_mtx, translateVector );
}

const glm::mat4 STransform::GetModelMTX() const {
	return _position_mtx;
}

STransform::STransform() :
	_position_mtx( glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)) )
{ }

STransform::STransform( glm::vec3 position, glm::vec3 rotation, glm::vec3 scale ) :
	_position_mtx( glm::translate(glm::mat4(1.0f), position) )
{ }

