#include "ClientChatSayPacket.h"

void ClientChatSayPacket::Parse(std::vector<uint8_t>& src) {
	BaseNetPacket::Parse(src);

	text = MinecraftTypes::ReadString(buff);
}
