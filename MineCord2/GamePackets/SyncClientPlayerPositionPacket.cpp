#include "SyncClientPlayerPositionPacket.h"

void SyncClientPlayerPositionPacket::Parse(std::vector<uint8_t>& src) {
	BaseNetPacket::Parse(src);

	x = buff.readDouble_BE();
	feetY = buff.readDouble_BE();
	z = buff.readDouble_BE();
	isOnGround = buff.readBool();
}
