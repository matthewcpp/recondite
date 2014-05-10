#include "rFrustrum.hpp"

bool rFrustrum::PointInFrustrum(const rVector3& p){
	return near.Side(p) > 0 && far.Side(p) > 0 &&
		top.Side(p) > 0 && bottom.Side(p) > 0 &&
		left.Side(p) > 0 && right.Side(p) > 0;
}