#include "SetCompressionPacket.h"

void SetCompressionPacket::Build(Buffer& dest) {
	PKT_BEGIN(SET_COMPRESSION_PACKETID);

	MinecraftTypes::WriteVarInt(buff, maxUncompressedSize);

	PKT_END();
}
