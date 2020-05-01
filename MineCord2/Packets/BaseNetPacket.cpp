#include "BaseNetPacket.h"
#include "../Utl.h"

void BaseNetPacket::Parse(std::vector<uint8_t>& src) {
	buff.setBuffer(src);

	length = MinecraftTypes::ReadVarInt(buff);
	packetId = MinecraftTypes::ReadVarInt(buff, &packetIdLen);

	if (isCompressed) {
		uncompressedLength = MinecraftTypes::ReadVarInt(buff);
	}
}
