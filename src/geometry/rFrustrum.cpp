#include "rFrustrum.hpp"

bool rFrustrum::PointInFrustrum(const rVector3& p){
	return	nearPlane.Side(p) > 0 && farPlane.Side(p) > 0 &&
		topPlane.Side(p) > 0 && bottomPlane.Side(p) > 0 &&
		leftPlane.Side(p) > 0 && rightPlane.Side(p) > 0;
}