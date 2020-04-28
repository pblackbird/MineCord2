#pragma once

#include "BaseNetPacket.h"

class StatusPacket : public BaseNetPacket {
public:
	int packetId = STATUS_PACKETID;
	std::string json;

public:
	virtual void Build(Buffer& dest) override;
};