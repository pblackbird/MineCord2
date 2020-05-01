#pragma once

#include "BaseNetPacket.h"

class LoginStartPacket : public BaseNetPacket {
public:
	std::string playerName;

public:
	LoginStartPacket() {
		isCompressed = false;
	}

	void Parse(std::vector<uint8_t>& src) override;
};