#include "UpdateViewPositionPacket.h"

void UpdateViewPositionPacket::Build(Buffer& dest) {
	packetId = UPDATE_VIEW_POSITION_PACKETID;

	MinecraftTypes::WriteVarInt(buff, chunkX);
	MinecraftTypes::WriteVarInt(buff, chunkZ);

	PKT_END();
}
