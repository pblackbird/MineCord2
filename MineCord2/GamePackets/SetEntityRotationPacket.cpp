#include "SetEntityRotationPacket.h"

void SetEntityRotationPacket::Build(Buffer& dest) {
	packetId = SET_ENTITY_ROTATION;

	MinecraftTypes::WriteVarInt(buff, id);
	buff.writeUInt8(pitchSteps);
	buff.writeUInt8(yawSteps);
	buff.writeBool(isOnGround);

	PKT_END();
}
