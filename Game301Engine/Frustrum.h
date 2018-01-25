#pragma once
#ifndef FRUSTRUM_H
#define FRUSTRUM_H

#include "Plane.h"
#include "BoundingVolume.h"

namespace ENGINE {

	class Frustrum
	{
	public:
		//Used to determine if an object is inside the frustum
		static enum EnclosureType {
			INSIDE, OUTSIDE, OVERLAP
		};

		Frustrum();
		~Frustrum();

		void windowResized(float angle_, float ratio_, float nearD_, float farD_);
		void cameraChanged(glm::vec3 &camPosn_, glm::vec3 &right_, glm::vec3 &up_, glm::vec3 &front_);

		//Determine if a point/Box/Sphere is inside the frustum. Returns a type depending if Inside, Outside, or Overlapp
		EnclosureType isInside(glm::vec3 &pt_);
		EnclosureType isInside(BoundingVolume* box_);
		EnclosureType isInside(glm::vec3 &cent_, float radius_);

	private:
		//The names of the 6 planes
		enum PlaneNames {
			PLANE_NEAR, PLANE_FAR, PLANE_TOP, PLANE_BOTTOM, PLANE_RIGHT, PLANE_LEFT
		};
		
		glm::vec3 camPos;									//The camera position at the apex of the frustum 
		glm::vec3 viewDir;									//A normalized vector looking in the same direction as the camera
		float nearDist;										//Distance from the camera to the near plane
		float farDist;										//Distance from the camera to the far plane
		glm::vec3 nearCent;									//The centre of the near plane
		glm::vec3 farCent;									//The centre of the far plane
		float nearWd;										//Width of the near plane
		float nearHt;										//Height of the near plane
		float farWd;										//Width of the far plane
		float farHt;										//Height of the far plane
		glm::vec3 upDir;									//A normalized vector pointing up WRT the camera
		glm::vec3 rightDir;									//A normalized vector pointing right WRT the camera
		Plane planes[6];									//The 6 planes delimiting the frustum
		glm::vec3 ntl, nbl, nbr, ntr, ftl, fbl, fbr, ftr;	//The corner points of the near and far planes
		float ratio;										//The ratio from the graphics system perspective calculations
		float angle;										//The angle of the field of view
		float tang;											//Tangent of half the angle
	};

}

#endif