#include "Frustrum.h"

using namespace ENGINE;

#define ANG2RAD 3.14159265358979323846/180.0

Frustrum::Frustrum()
{
}

Frustrum::~Frustrum()
{
}

void Frustrum::windowResized(float angle_, float ratio_, float nearD_, float farD_)
{
	angle = angle_;
	ratio = ratio_;
	nearDist = nearD_;
	farDist = farD_;

	//Compute width & height of near & far planes
	tang = (float)tan(ANG2RAD * angle * 0.5);
	nearHt = nearDist * tang;
	nearWd = nearHt * ratio;
	farHt = farDist * tang;
	farWd = farHt * ratio;
}

void Frustrum::cameraChanged(glm::vec3 &camPosn_, glm::vec3 &right_, glm::vec3 &up_, glm::vec3 &front_)
{
	//Compute centres of near and far planes
	nearCent = camPosn_ - (front_ * nearDist);
	farCent = camPosn_ - (front_ * farDist);

	//Compute 4 corners of near plane
	ntl = nearCent + up_ * nearHt - right_ * nearWd;
	ntr = nearCent + up_ * nearHt + right_ * nearWd;
	nbl = nearCent - up_ * nearHt - right_ * nearWd;
	nbr = nearCent - up_ * nearHt + right_ * nearWd;

	//Compute 4 corners of far plane
	ftl = farCent + up_ * farHt - right_ * farWd;
	ftr = farCent + up_ * farHt + right_ * farWd;
	fbl = farCent - up_ * farHt - right_ * farWd;
	fbr = farCent - up_ * farHt + right_ * farWd;

	//Compute the 6 planes
	planes[PLANE_TOP] = Plane(ntr, ntl, ftl);
	planes[PLANE_BOTTOM] = Plane(nbl, nbr, fbr);
	planes[PLANE_LEFT] = Plane(ntl, nbl, fbl);
	planes[PLANE_RIGHT] = Plane(nbr, ntr, fbr);
	planes[PLANE_NEAR] = Plane(ntl, ntr, nbr);
	planes[PLANE_FAR] = Plane(ftr, ftl, fbl);
}

Frustrum::EnclosureType Frustrum::isInside(glm::vec3 &pt_)
{
	for (int i = 0; i < 6; i++)
	{
		if (planes[i].signedDistance(pt_) < 0)
		{
			return OUTSIDE;
		}
	}
	return INSIDE;
}

Frustrum::EnclosureType Frustrum::isInside(BoundingVolume* box_)
{
	EnclosureType result = INSIDE;

	for (int i = 0; i < 6; i++)
	{
		//Test positive vertex to see if it is outside
		if (planes[i].signedDistance(box_->getPositiveVertex(planes[i].getNormal())) < 0)
			return OUTSIDE;
		//Is negative vertex outside?
		else if (planes[i].signedDistance(box_->getNegativeVertex(planes[i].getNormal())) < 0)
			return OVERLAP;
	}
	return result;
}

Frustrum::EnclosureType Frustrum::isInside(glm::vec3 &cent_, float radius_)
{
	float distance;
	EnclosureType result = INSIDE;

	for (int i = 0; i < 6; i++)
	{
		distance = planes[i].signedDistance(cent_);
		if (distance < -radius_) return OUTSIDE;
		else if (distance < radius_) result = OVERLAP;
	}
	return result;
}
