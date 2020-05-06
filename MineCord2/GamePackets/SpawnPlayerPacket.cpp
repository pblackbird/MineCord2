#include "SpawnPlayerPacket.h"

void SpawnPlayerPacket::Build(Buffer& dest) {
	PKT_BEGIN(SPAWN_PLAYER_PACKETID);

	const auto stepAngle = Transformable::GetStepByAngle(rotation);

	MinecraftTypes::WriteVarInt(buff, id);
	MinecraftTypes::WriteUUID(buff, uuid);

	buff.writeDouble_BE(position.x);
	buff.writeDouble_BE(position.y);
	buff.writeDouble_BE(position.z);

	buff.writeUInt8(stepAngle.yaw);
	buff.writeUInt8(stepAngle.pitch);

	for (const auto byte : metadata) {
		buff.writeUInt8(byte);
	}

	PKT_END();
}
