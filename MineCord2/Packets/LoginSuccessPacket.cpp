#include "LoginSuccessPacket.h"

void LoginSuccessPacket::Build(Buffer& dest) {
	packetId = 0x02;

	MinecraftTypes::WriteString(buff, uuid);
	MinecraftTypes::WriteString(buff, playerName);

	PKT_END();
}
