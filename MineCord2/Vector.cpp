#include "Vector.h"

float Vector::DotProduct(Vector a, Vector b) {
	return (float)(a.direction.x * b.direction.x 
		+ a.direction.y * b.direction.y 
		+ a.direction.z * b.direction.z);
}

float Vector::GetAngleBetween(Vector a, Vector b) {
	return std::acos(Vector::DotProduct(a.Normalize(), b.Normalize()));
}

float Vector::GetDistance(Vector a, Vector b) {
	return (a - b).GetLength();
}

Vector Vector::Normalize() const {
	const auto len = GetLength();

	return Vector({
		direction.x / len,
		direction.y / len,
		direction.z / len
	});
}

float Vector::GetLength() const {
	return std::sqrt(Vector::DotProduct(*this, *this));
}

Vector Vector::operator*(float scalar) {
	return Vector({
		direction.x * scalar,
		direction.y * scalar,
		direction.z * scalar
	});
}

Vector Vector::operator+(Vector b) {
	return Vector({
		direction.x + b.direction.x,
		direction.y + b.direction.y,
		direction.z + b.direction.z
	});
}

Vector Vector::operator-(Vector b) {
	return Vector({
		direction.x - b.direction.x,
		direction.y - b.direction.y,
		direction.z - b.direction.z
	});
}
