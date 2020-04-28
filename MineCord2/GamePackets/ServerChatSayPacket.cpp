#include "ServerChatSayPacket.h"

void ServerChatSayPacket::Build(Buffer& dest) {
	packetId = CHAT_MSG_FROM_SERVER_PACKETID;

	MinecraftTypes::WriteString(buff, m_json);
	buff.writeUInt8((uint8_t)type);

	PKT_END();
}
