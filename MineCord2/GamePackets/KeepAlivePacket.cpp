#include "KeepAlivePacket.h"

void KeepAlivePacket::Parse(std::vector<uint8_t>& src) {
	BaseNetPacket::Parse(src);

	keepAliveId = buff.readInt64_BE();
}

void KeepAlivePacket::Build(Buffer& dest) {
	PKT_BEGIN(KEEP_ALIVE_PACKETID);

	buff.writeInt64_BE(keepAliveId);

	PKT_END();
}
