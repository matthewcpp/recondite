#include "rFrustrum.hpp"


bool rFrustrum::PointInFrustrum(const rVector3& p){
	return pNear.Side(p) > 0 && pFar.Side(p) > 0 &&
		pTop.Side(p) > 0 && pBottom.Side(p) > 0 &&
		pLeft.Side(p) > 0 && pRight.Side(p) > 0;
}