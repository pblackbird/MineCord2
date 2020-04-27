#include "LoginStartPacket.h"

void LoginStartPacket::Parse(std::vector<uint8_t>& src) {
	BaseNetPacket::Parse(src);

	playerName = MinecraftTypes::ReadString(buff);
}
