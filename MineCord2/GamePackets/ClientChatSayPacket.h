#pragma once

#include "../Packets/BaseNetPacket.h"

class ClientChatSayPacket : public BaseNetPacket {
public:
	std::string text;

public:
	virtual void Parse(std::vector<uint8_t>& src) override;
};