#include "UpdateViewPositionPacket.h"

void UpdateViewPositionPacket::Build(Buffer& dest) {
	PKT_BEGIN(UPDATE_VIEW_POSITION_PACKETID);

	MinecraftTypes::WriteVarInt(buff, chunkX);
	MinecraftTypes::WriteVarInt(buff, chunkZ);

	PKT_END();
}
