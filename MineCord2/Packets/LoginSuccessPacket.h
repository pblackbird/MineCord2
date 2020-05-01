#pragma once

#include "BaseNetPacket.h"

class LoginSuccessPacket : public BaseNetPacket {
public:
	std::string playerName;
	std::string uuid;

public:
	LoginSuccessPacket() {
		isCompressed = true;
	}

	virtual void Build(Buffer& dest) override;
};