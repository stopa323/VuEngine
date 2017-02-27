/*
 * STransform.h
 *
 *  Created on: Feb 27, 2017
 *      Author: root
 */

#ifndef ENGINE_GAME_ENTITY_STRANSFORM_H_
#define ENGINE_GAME_ENTITY_STRANSFORM_H_

#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>


struct STransform {
public:
	STransform();
//	STransform( const STransform* parent );
	STransform( glm::vec3 position, glm::vec3 rotation, glm::vec3 scale );
//	STransform( const STransform* parent, glm::vec3 position, glm::vec3 rotation,
//			glm::vec3 scale );

	const glm::vec3 GetPosition() const;
//	const glm::vec3 GetWorldPosition() const;
	void Translate( glm::vec3 translateVector );
	const glm::mat4 GetModelMTX() const;

private:
	glm::mat4 _position_mtx;
//	glm::vec3 _rotation;
//	glm::vec3 _scale;

//	const STransform* _parent_transform;
};

#endif /* ENGINE_GAME_ENTITY_STRANSFORM_H_ */
