#include "SetCompressionPacket.h"

void SetCompressionPacket::Build(Buffer& dest) {
	packetId = SET_COMPRESSION_PACKETID;

	MinecraftTypes::WriteVarInt(buff, maxUncompressedSize);

	PKT_END();
}
