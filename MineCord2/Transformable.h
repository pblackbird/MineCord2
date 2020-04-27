#pragma once

#include <stdint.h>

#define TF_X 0x01
#define TF_Y 0x02
#define TF_Z 0x04

#define TF_Y_ROT 0x08
#define TF_X_ROT 0x10

typedef struct {
	double x;
	double y;
	double z;
} Point3D;

typedef struct {
	float pitch;
	float yaw;
} Angle;

class Transformable {
protected:
	Point3D position;
	Angle rotation;
	uint8_t transformationFlags;

private:
	void AcquirePosition(Point3D aPos);
	void AcquireRotation(Angle ang);

public:

	void Move(double x, double y, double z);
	void Rotate(float pitch, float yaw);

	void SetPosition(double x, double y, double z);
	void SetPosition(Point3D pos);

	void SetRotation(float pitch, float yaw);
	void SetRotation(Angle ang);

	Point3D GetPosition();
	Angle GetRotation();

	uint8_t ApplyTransformations();
};