#include "LoginSuccessPacket.h"

void LoginSuccessPacket::Build(Buffer& dest) {
	packetId = LOGIN_SUCCESS_PACKETID;

	MinecraftTypes::WriteString(buff, uuid);
	MinecraftTypes::WriteString(buff, playerName);

	PKT_END();
}
