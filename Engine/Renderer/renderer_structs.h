/*
 * renderer_structs.h
 *
 *  Created on: Mar 9, 2017
 *      Author: root
 */

#ifndef ENGINE_RENDERER_RENDERER_STRUCTS_H_
#define ENGINE_RENDERER_RENDERER_STRUCTS_H_

#include <glm/gtc/matrix_transform.hpp>

struct SProjectionMatrix {
	float FieldOfView;			// degrees
	float AspectRatio;  		// screen_width / screen_height
	float NearClippingPlane;
	float FarClippingPlane;

	const glm::mat4 GetMatrix() const {
		auto mtx = glm::perspective( FieldOfView, AspectRatio, NearClippingPlane,
				FarClippingPlane );
		mtx[1][1] *= -1;
		return mtx;
	}
};


#endif /* ENGINE_RENDERER_RENDERER_STRUCTS_H_ */
