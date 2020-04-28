#pragma once

#include "BaseNetPacket.h"

class HandshakePacket : public BaseNetPacket {
public:
	int protocolVersion;
	std::string serverAddress;
	uint16_t serverPort;
	int nextState;

	int packetId = HANDSHAKE_PACKETID;

public:
	void Parse(std::vector<uint8_t>& src) override;
};