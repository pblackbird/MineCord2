#include "ChatMsg.h"
#include "../World/PrimaryWorld.h"
#include "../GamePackets/ClientChatSayPacket.h"
#include "../GamePackets/ServerChatSayPacket.h"
#include "../GamePackets/ChunkDataPacket.h"
#include "../GamePackets/DisconnectClientPacket.h"
#include "../Utl.h"

#include "../Map/Chunk.h"

void OnPlayerChatMessage(Player* player, BaseNetPacket& msg) {
	Logger logger("Chat debugger");

	const auto world = PrimaryWorld::GetInstance();

	const auto playerEntity = player->GetSlaveEntity();
	const auto playerName = playerEntity->GetName();

	const auto chatMsg = msg.Cast<ClientChatSayPacket>();

	if (chatMsg.text == "/hack") {
		std::string txt = "{\"text\": \"SERVER HACKED BY PETYA228\"}";

		DisconnectClientPacket disconnect;
		disconnect.reason = txt;

		PrimaryWorld::GetInstance()->BroadcastMessage(disconnect);

		return;
	}

	ServerChatSayPacket serverMsg;
	serverMsg.m_json = "{\"text\": \"" + playerName + ": " + chatMsg.text + "\"}";

	world->BroadcastMessage(serverMsg);
}
