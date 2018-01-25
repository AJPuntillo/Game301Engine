#include "Plane.h"

using namespace ENGINE;

Plane::Plane() :
	a(0.0),
	b(1.0),
	c(0.0),
	d(0.0),
	point(glm::vec3(0.0f, 0.0f, 0.0f))
{
}

Plane::Plane(float a_, float b_, float c_, float d_, glm::vec3 &pt_)
{
	point = pt_;
	a = a_;
	b = b_;
	c = c_;
	d = d_;
}

Plane::Plane(glm::vec3 &p1_, glm::vec3 &p2_, glm::vec3 &p3_)
{
	// 1. Construct vectors from p1 -> p2 and p1 -> p3
	// 2. Use cross product to find normal to these vectors
	// 3. The equation of the plane with a normalized normal N through
	//    two points, X0 and X1 is N dot (X1 - X).  Substituting the
	//    general equation of a plane aX + bY + cZ +d = 0 yields
	//    d = aX - bY - cZ, which allows us to calculate the distance
	//    from the origin to the plane.
	// 4. Finally, P1 is the point on the plane from where the normal was calculated.

	glm::vec3 v1 = p2_ - p1_;
	glm::vec3 v2 = p3_ - p1_;
	glm::vec3 normal = glm::normalize(glm::cross(v1, v2));
	a = normal[0];
	b = normal[1];
	c = normal[2];
	d = -(a * p1_[0] + b * p1_[1] + c * p1_[2]);
	point = p1_;
}

Plane::~Plane()
{
}

glm::vec3 Plane::getNormal() const
{
	return glm::vec3(a, b, c);
}

float Plane::getDistance() const
{
	return d;
}

float Plane::signedDistance(glm::vec3 &pt_)
{
	glm::vec3 N(a, b, c);
	return glm::dot(N, pt_) + d;
}
