#pragma once

#include "BaseNetPacket.h"

class PingPacket : public BaseNetPacket {
public:
	uint64_t payload;
	int packetId = 0x01;

public:
	void Parse(std::vector<uint8_t>& src) override;
	void Build(Buffer& dest) override;
};