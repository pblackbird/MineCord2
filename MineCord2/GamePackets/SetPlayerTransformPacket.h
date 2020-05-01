#pragma once

#include "../Packets/BaseNetPacket.h"

class SetPlayerTransformPacket : public BaseNetPacket {
public:
	double x, y, z;
	float pitch, yaw;
	uint8_t flags;
	int teleportId;

public:
	SetPlayerTransformPacket() {
		isCompressed = true;
	}

	virtual void Build(Buffer& dest) override;
};