#include "ChatMsg.h"
#include "../GamePackets/ClientChatSayPacket.h"

void OnPlayerChatMessage(Player* player, BaseNetPacket& msg) {
	const auto playerEntity = player->GetSlaveEntity();
	const auto playerName = playerEntity->GetName();

	const auto chatMsg = msg.Cast<ClientChatSayPacket>();

	logger.Info(
		L"%ls said %ls", 
		std::wstring(playerName.begin(), playerName.end()).c_str(),
		std::wstring(chatMsg.text.begin(), chatMsg.text.end()).c_str()
	);
}
