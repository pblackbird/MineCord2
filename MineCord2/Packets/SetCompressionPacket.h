#pragma once

#include "BaseNetPacket.h"

class SetCompressionPacket : public BaseNetPacket {
public:
	int packetId = SET_COMPRESSION_PACKETID;
	int maxUncompressedSize = 1024;

public:
	SetCompressionPacket() {
		isCompressed = false;
	}

	void Build(Buffer& dest) override;
};