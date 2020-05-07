#include "EntityHeadLookPacket.h"

void EntityHeadLookPacket::Build(Buffer& dest) {
	PKT_BEGIN(ENTITY_HEAD_LOOK_PACKETID);

	MinecraftTypes::WriteVarInt(buff, id);
	buff.writeUInt8(headYaw);

	PKT_END();
}
