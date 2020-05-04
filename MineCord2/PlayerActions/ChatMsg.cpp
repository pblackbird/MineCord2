#include "ChatMsg.h"
#include "../World/PrimaryWorld.h"
#include "../GamePackets/ClientChatSayPacket.h"
#include "../GamePackets/ServerChatSayPacket.h"
#include "../GamePackets/ChunkDataPacket.h"

#include "../Map/Chunk.h"

void OnPlayerChatMessage(Player* player, BaseNetPacket& msg) {
	Logger logger("Chat debugger");

	const auto world = PrimaryWorld::GetInstance();

	const auto playerEntity = player->GetSlaveEntity();
	const auto playerName = playerEntity->GetName();

	const auto chatMsg = msg.Cast<ClientChatSayPacket>();

	ServerChatSayPacket serverMsg;
	serverMsg.m_json = "{\"text\": \"" + playerName + ": " + chatMsg.text + "\"}";

	world->BroadcastMessage(serverMsg);
}
