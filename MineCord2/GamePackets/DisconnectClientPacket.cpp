#include "DisconnectClientPacket.h"

void DisconnectClientPacket::Build(Buffer& dest) {
	PKT_BEGIN(DISCONNECT_PLAYER_PACKETID);

	MinecraftTypes::WriteString(buff, reason);

	PKT_END();
}
