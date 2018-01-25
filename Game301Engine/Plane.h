#pragma once
#ifndef PLANE_H
#define PLANE_H

#include <glm/glm.hpp>

namespace ENGINE {

	class Plane
	{
	public:
		Plane();
		Plane(float a_, float b_, float c_, float d_, glm::vec3 &pt_);
		Plane::Plane(glm::vec3 &p1_, glm::vec3 &p2_, glm::vec3 &p3_); //Contruct a plane based on 3 vectors
		~Plane();

		glm::vec3 getNormal() const;
		float getDistance() const;
		float signedDistance(glm::vec3 &pt); //Determines which side of the plane the point is on

	private:
		//This is a point on the plane
		glm::vec3 point;
		//These are the multipliers for the equation of the plane aX + bY + cZ +d = 0 
		float a, b, c, d;
	};

}

#endif