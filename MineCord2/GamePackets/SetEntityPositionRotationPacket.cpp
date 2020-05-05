#include "SetEntityPositionRotationPacket.h"

void SetEntityPositionRotationPacket::Build(Buffer& dest) {
	PKT_BEGIN(SET_ENTITY_ROTATION_POSITION);
	
	MinecraftTypes::WriteVarInt(buff, id);

	PKT_END();
}
