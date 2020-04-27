#include "HandshakePacket.h"

void HandshakePacket::Parse(std::vector<uint8_t>& src) {
	BaseNetPacket::Parse(src);

	protocolVersion = MinecraftTypes::ReadVarInt(buff);
	serverAddress = MinecraftTypes::ReadString(buff);
	serverPort = buff.readUInt16_BE();
	nextState = MinecraftTypes::ReadVarInt(buff);
}
