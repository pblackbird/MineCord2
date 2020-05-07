#pragma once

#include "../Packets/BaseNetPacket.h"
#include "../Transformable.h"

class SetEntityPositionRotationPacket : public BaseNetPacket {
public:
	entity_id id;
	Point3D deltaPosition;
	AngleStep angle;
	bool isOnGround;

public:
	SetEntityPositionRotationPacket() {
		isCompressed = true;
	}

	virtual void Build(Buffer& dest) override;
};