#pragma once

#include "../Packets/BaseNetPacket.h"

class SetEntityRotationPacket : public BaseNetPacket {
public:
	entity_id id;
	uint8_t pitchSteps, yawSteps;

	bool isOnGround;

public:
	SetEntityRotationPacket() {
		isCompressed = true;
	}

	virtual void Build(Buffer& dest) override;
};