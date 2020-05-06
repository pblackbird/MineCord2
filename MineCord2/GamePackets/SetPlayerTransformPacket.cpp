#include "SetPlayerTransformPacket.h"

void SetPlayerTransformPacket::Build(Buffer& dest) {
	PKT_BEGIN(UPDATE_PLAYER_ANGLE_POS_PACKETID);

	buff.writeDouble_BE(x);
	buff.writeDouble_BE(y);
	buff.writeDouble_BE(z);
	buff.writeFloat_BE(pitch);
	buff.writeFloat_BE(yaw);
	buff.writeInt8(flags);
	MinecraftTypes::WriteVarInt(buff, teleportId);

	PKT_END();
}
