#pragma once

#include "BaseNetPacket.h"

class PingPacket : public BaseNetPacket {
public:
	uint64_t payload;
	int packetId = PING_PONG_PACKETID;

public:
	void Parse(std::vector<uint8_t>& src) override;
	void Build(Buffer& dest) override;
};