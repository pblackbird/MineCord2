#pragma once

#include "../Packets/BaseNetPacket.h"

class SyncClientPlayerRotationPacket : public BaseNetPacket {
public:
	float yaw;
	float pitch;
	bool isOnGround;

public:
	SyncClientPlayerRotationPacket() {
		isCompressed = true;
	}

	virtual void Parse(std::vector<uint8_t>& src) override;
};