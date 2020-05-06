#include "SpawnPlayerPacket.h"

void SpawnPlayerPacket::Build(Buffer& dest) {
	PKT_BEGIN(SPAWN_PLAYER_PACKETID);

	MinecraftTypes::WriteVarInt(buff, id);
	MinecraftTypes::WriteUUID(buff, uuid);
	buff.writeDouble_BE(position.x);
	buff.writeDouble_BE(position.y);
	buff.writeDouble_BE(position.z);
	buff.writeUInt8((uint8_t)rotation.yaw);
	buff.writeUInt8((uint8_t)rotation.pitch);

	for (const auto byte : metadata) {
		buff.writeUInt8(byte);
	}

	PKT_END();
}
