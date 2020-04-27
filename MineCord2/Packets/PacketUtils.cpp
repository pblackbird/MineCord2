#include "PacketUtils.h"

void PacketUtils::Write(Buffer& in, Buffer& out, int pktId, size_t pktIdLen) {
	MinecraftTypes::WriteVarInt(out, in.getBuffer().size() + pktIdLen);
	MinecraftTypes::WriteVarInt(out, pktId);

	for (size_t i = 0; i < in.getBuffer().size(); i++) {
		out.writeUInt8(in.getBuffer().at(i));
	}
}
