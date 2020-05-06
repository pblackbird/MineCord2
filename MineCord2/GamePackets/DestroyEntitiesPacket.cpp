#include "DestroyEntitiesPacket.h"

void DestroyEntitiesPacket::Build(Buffer& dest) {
	PKT_BEGIN(DESTROY_ENTITIES_PACKETID);

	MinecraftTypes::WriteVarInt(buff, entities.size());

	for (const auto entityId : entities) {
		MinecraftTypes::WriteVarInt(buff, entityId);
	}

	PKT_END();
}
