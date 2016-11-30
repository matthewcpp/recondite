#include "rMathUtil.hpp"

namespace rMath {
	float DegreeToRad(float deg) {
		return deg * (rPI / 180.0f);
	}

	float RadToDeg(float rad) {
		return rad * (180.0f / rPI);
	}

	float ConvertRange(float value, float inMin, float inMax, float outMin, float outMax) {
		return outMin + ((value - inMin) / (inMax - inMin)) * (outMax - outMin);
	}

	float Max3(float n1, float n2, float n3) {
		if (n1 > n2) {
			if (n1 > n3)
				return n1;
			else
				return n3;
		}
		else {
			if (n2 > n3)
				return n2;
		}

		return n3;
	}

	uint32_t NextHighestPowerOf2(uint32_t v) {
		v--;
		v |= v >> 1;
		v |= v >> 2;
		v |= v >> 4;
		v |= v >> 8;
		v |= v >> 16;
		v++;
		v += (v == 0);

		return v;
	}
}
