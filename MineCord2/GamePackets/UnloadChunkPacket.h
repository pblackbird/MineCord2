#pragma once

#include "../Packets/BaseNetPacket.h"

class UnloadChunkPacket : public BaseNetPacket {
public:
	int32_t x, z;

public:
	UnloadChunkPacket() {
		isCompressed = true;
	}

	virtual void Build(Buffer& dest) override;
};