#pragma once

#include "../Packets/BaseNetPacket.h"

class KeepAlivePacket : public BaseNetPacket {
public:
	int64_t keepAliveId;

public:
	KeepAlivePacket() {
		isCompressed = true;
	}

	virtual void Parse(std::vector<uint8_t>& src) override;
	virtual void Build(Buffer& dest) override;
};