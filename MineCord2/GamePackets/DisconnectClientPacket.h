#pragma once

#include "../Packets/BaseNetPacket.h"

class DisconnectClientPacket : public BaseNetPacket {
public:
	std::string reason;

public:
	DisconnectClientPacket() {
		isCompressed = true;
	}

	virtual void Build(Buffer& dest) override;
};