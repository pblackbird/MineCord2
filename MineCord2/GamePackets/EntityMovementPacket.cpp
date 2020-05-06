#include "EntityMovementPacket.h"

void EntityMovementPacket::Build(Buffer& dest) {
	PKT_BEGIN(ENTITY_MOVEMENT_PACKETID);

	MinecraftTypes::WriteVarInt(buff, id);

	PKT_END();
}
