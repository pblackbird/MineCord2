#include "PingPacket.h"

void PingPacket::Parse(std::vector<uint8_t>& src) {
	BaseNetPacket::Parse(src);

	payload = buff.readInt64_BE();
}

void PingPacket::Build(Buffer& dest) {
	PKT_BEGIN(PING_PONG_PACKETID);

	buff.writeInt64_BE(payload);

	PKT_END();
}
