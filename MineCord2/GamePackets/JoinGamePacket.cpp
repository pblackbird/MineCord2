#include "JoinGamePacket.h"

void JoinGamePacket::Build(Buffer& dest) {
	PKT_BEGIN(JOIN_GAME_PACKETID);

	buff.writeInt32_BE(entityId);
	buff.writeUInt8((uint8_t)gamemode);
	buff.writeInt32_BE((int32_t)dimension);
	buff.writeUInt8(maxPlayers);
	MinecraftTypes::WriteString(buff, worldType);
	MinecraftTypes::WriteVarInt(buff, viewDistance);
	buff.writeUInt8((uint8_t)isDebug);

	PKT_END();
}
