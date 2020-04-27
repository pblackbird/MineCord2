#pragma once

#include "BaseNetPacket.h"

class StatusPacket : public BaseNetPacket {
public:
	int packetId = 0x00;
	std::string json;

public:
	virtual void Build(Buffer& dest) override;
};