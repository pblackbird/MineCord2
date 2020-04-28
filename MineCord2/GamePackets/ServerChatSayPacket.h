#pragma once

#include "../Packets/BaseNetPacket.h"

class ServerChatSayPacket : public BaseNetPacket {
public:
	std::string m_json;
	ServerChatMessageType type;

public:
	virtual void Build(Buffer& dest) override;
};