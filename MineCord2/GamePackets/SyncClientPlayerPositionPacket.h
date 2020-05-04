#pragma once

#include "../Packets/BaseNetPacket.h"

class SyncClientPlayerPositionPacket : public BaseNetPacket {
public:
	double x;
	double feetY;
	double z;
	bool isOnGround;

public:
	SyncClientPlayerPositionPacket() {
		isCompressed = true;
	}

	virtual void Parse(std::vector<uint8_t>& src) override;
};