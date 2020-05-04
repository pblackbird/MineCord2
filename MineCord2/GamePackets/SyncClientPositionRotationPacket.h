#pragma once

#include "../Packets/BaseNetPacket.h"

class SyncClientPositionRotationPacket : public BaseNetPacket {
public:
	double x;
	double feetY;
	double z;
	float pitch;
	float yaw;
	bool isOnGround;

public:
	SyncClientPositionRotationPacket() {
		isCompressed = true;
	}

	virtual void Parse(std::vector<uint8_t>& src) override;
};