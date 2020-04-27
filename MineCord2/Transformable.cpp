#include "Transformable.h"
#include "Utl.h"

void Transformable::AcquirePosition(Point3D aPos) {
	if (aPos.x != 0) {
		Utl::SetBit((int&)transformationFlags, TF_X);
	}

	if (aPos.y != 0) {
		Utl::SetBit((int&)transformationFlags, TF_Y);
	}

	if (aPos.z != 0) {
		Utl::SetBit((int&)transformationFlags, TF_Z);
	}
}

void Transformable::AcquireRotation(Angle ang) {
	if (ang.pitch != 0.0f) {
		Utl::SetBit((int&)transformationFlags, TF_X_ROT);
	}

	if (ang.yaw != 0.0f) {
		Utl::SetBit((int&)transformationFlags, TF_Y_ROT);
	}
}

void Transformable::Rotate(float pitch, float yaw) {
	SetRotation(rotation.pitch + pitch, rotation.yaw + yaw);
}

void Transformable::SetRotation(float pitch, float yaw) {
	rotation.pitch = pitch;
	rotation.yaw = yaw;

	AcquireRotation({
		pitch, yaw
	});
}

void Transformable::SetRotation(Angle ang) {
	rotation = ang;
	AcquireRotation(ang);
}

void Transformable::SetPosition(double x, double y, double z) {
	position.x = x;
	position.y = y;
	position.z = z;

	AcquirePosition({
		x, y, z
	});
}

void Transformable::SetPosition(Point3D pos) {
	position = pos;
	AcquirePosition(pos);
}

void Transformable::Move(double x, double y, double z) {
	SetPosition(position.x + x, position.y + y, position.z + z);
}

Point3D Transformable::GetPosition() {
	return position;
}

Angle Transformable::GetRotation() {
	return rotation;
}

uint8_t Transformable::ApplyTransformations() {
	uint8_t ret = transformationFlags;
	transformationFlags = 0;

	return ret;
}
