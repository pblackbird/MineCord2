#include "SetEntityPositionRotationPacket.h"

void SetEntityPositionRotationPacket::Build(Buffer& dest) {
	PKT_BEGIN(SET_ENTITY_ROTATION_POSITION);
	
	MinecraftTypes::WriteVarInt(buff, id);
	buff.writeInt16_BE((int16_t)deltaPosition.x);
	buff.writeInt16_BE((int16_t)deltaPosition.y);
	buff.writeInt16_BE((int16_t)deltaPosition.z);

	buff.writeUInt8(angle.yaw);
	buff.writeUInt8(angle.pitch);

	buff.writeBool(isOnGround);

	PKT_END();
}
