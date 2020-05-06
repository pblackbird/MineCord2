#include "StatusPacket.h"

void StatusPacket::Build(Buffer& dest) {
	PKT_BEGIN(STATUS_PACKETID);

	MinecraftTypes::WriteString(buff, json);

	PKT_END();
}
