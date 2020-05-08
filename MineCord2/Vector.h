#pragma once

#include <cmath>

#include "Transformable.h"

class Vector {
public:
	Point3D direction;

public:
	Vector(Point3D dir) : direction(dir) {};
	Vector() {};

	Point3D GetDirection() {
		return direction;
	}

	static float DotProduct(Vector a, Vector b);
	static float GetAngleBetween(Vector a, Vector b);
	static float GetDistance(Vector a, Vector b);
	
	Vector Normalize() const;
	float GetLength() const;

	Vector operator*(float scalar);
	Vector operator+(Vector b);
	Vector operator-(Vector b);
};