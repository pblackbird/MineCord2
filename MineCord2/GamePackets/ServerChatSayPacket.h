#pragma once

#include "../Packets/BaseNetPacket.h"

class ServerChatSayPacket : public BaseNetPacket {
public:
	std::string m_json;
	ServerChatMessageType type;

public:
	ServerChatSayPacket() {
		isCompressed = true;
	}

	virtual void Build(Buffer& dest) override;
};