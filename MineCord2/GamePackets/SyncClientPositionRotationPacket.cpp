#include "SyncClientPositionRotationPacket.h"

void SyncClientPositionRotationPacket::Parse(std::vector<uint8_t>& src) {
	BaseNetPacket::Parse(src);

	x = buff.readDouble_BE();
	feetY = buff.readDouble_BE();
	z = buff.readDouble_BE();
	yaw = buff.readFloat_BE();
	pitch = buff.readFloat_BE();
	isOnGround = buff.readBool();
}
