#include "StatusPacket.h"

void StatusPacket::Build(Buffer& dest) {
	MinecraftTypes::WriteString(buff, json);

	PKT_END();
}
