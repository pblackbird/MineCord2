#include "ChatMsg.h"
#include "../World/PrimaryWorld.h"
#include "../GamePackets/ClientChatSayPacket.h"
#include "../GamePackets/ServerChatSayPacket.h"
#include "../GamePackets/ChunkDataPacket.h"

#include "../Map/Chunk.h"

void OnPlayerChatMessage(Player* player, BaseNetPacket& msg) {
	Logger logger(L"Chat debugger");

	const auto world = PrimaryWorld::GetInstance();

	const auto playerEntity = player->GetSlaveEntity();
	const auto playerName = playerEntity->GetName();

	const auto chatMsg = msg.Cast<ClientChatSayPacket>();

	logger.Info(
		L"%ls said %ls", 
		std::wstring(playerName.begin(), playerName.end()).c_str(),
		std::wstring(chatMsg.text.begin(), chatMsg.text.end()).c_str()
	);

	if (chatMsg.text == "/chunk") {
		Chunk testChunk;
		testChunk.SetPosition({ 10, 5 });

		// Fill 16 chunk sections per chunk
		for (int i = 0; i < 16; i++) {
			ChunkSection section;

			// Fill 16 blocks per chunk section
			for (int j = 0; j < 16; j++) {
				Block testBlock;
				testBlock.palette = 1;

				section.SetBlock(j, testBlock);
			}

			testChunk.SetSection(i, section);
		}

		ChunkDataPacket chunkMsg;
		chunkMsg.chunk = testChunk;

		player->GetNetClient()->Invoke(chunkMsg);

		return;
	}

	ServerChatSayPacket serverMsg;
	serverMsg.m_json = "{\"text\": \"Baba bebe\"}";

	world->BroadcastMessage(serverMsg);
}
