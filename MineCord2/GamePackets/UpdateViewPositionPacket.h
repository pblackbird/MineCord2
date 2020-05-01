#pragma once

#include "../Packets/BaseNetPacket.h"

class UpdateViewPositionPacket : public BaseNetPacket {
public:
	uint32_t chunkX, chunkZ;

public:
	UpdateViewPositionPacket() {
		isCompressed = true;
	}

	virtual void Build(Buffer& dest) override;
};