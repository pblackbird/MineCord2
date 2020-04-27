#include "BaseNetPacket.h"

void BaseNetPacket::Parse(std::vector<uint8_t>& src) {
	buff.setBuffer(src);

	length = MinecraftTypes::ReadVarInt(buff);
	packetId = MinecraftTypes::ReadVarInt(buff, &packetIdLen);
}
