#include "Math.h"

float Math::Deg2Rad(float deg) {
	return deg * (float)M_PI / 180.f;
}

float Math::Rad2Deg(float rad) {
	return rad * 180.f / (float)M_PI;
}
