#include "SetEntityRotationPacket.h"

void SetEntityRotationPacket::Build(Buffer& dest) {
	PKT_BEGIN(SET_ENTITY_ROTATION);

	MinecraftTypes::WriteVarInt(buff, id);
	buff.writeUInt8(pitchSteps);
	buff.writeUInt8(yawSteps);
	buff.writeBool(isOnGround);

	PKT_END();
}
