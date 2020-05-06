#include "LoginSuccessPacket.h"

void LoginSuccessPacket::Build(Buffer& dest) {
	PKT_BEGIN(LOGIN_SUCCESS_PACKETID);

	MinecraftTypes::WriteString(buff, uuid);
	MinecraftTypes::WriteString(buff, playerName);

	PKT_END();
}
