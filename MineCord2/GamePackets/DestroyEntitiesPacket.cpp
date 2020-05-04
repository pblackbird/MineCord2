#include "DestroyEntitiesPacket.h"

void DestroyEntitiesPacket::Build(Buffer& dest) {
	packetId = DESTROY_ENTITIES_PACKETID;

	MinecraftTypes::WriteVarInt(buff, entities.size());

	for (const auto entityId : entities) {
		MinecraftTypes::WriteVarInt(buff, entityId);
	}

	PKT_END();
}
