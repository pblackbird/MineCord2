#include "SyncClientPlayerRotationPacket.h"

void SyncClientPlayerRotationPacket::Parse(std::vector<uint8_t>& src) {
	BaseNetPacket::Parse(src);

	yaw = buff.readFloat_BE();
	pitch = buff.readFloat_BE();
	isOnGround = buff.readBool();
}
