#ifndef R_FRUSTRUM_HPP
#define R_FRUSTRUM_HPP

#include "rPlane3.hpp"
#include "rVector3.hpp"

struct rFrustrum{
	rFrustrum(){}

	bool PointInFrustrum(const rVector3& p);

	rPlane3 nearPlane;
	rPlane3 farPlane; 
	rPlane3 topPlane; 
	rPlane3 bottomPlane;
	rPlane3 leftPlane;
	rPlane3 rightPlane;
};

#endif