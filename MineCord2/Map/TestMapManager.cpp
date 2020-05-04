#include "TestMapManager.h"
#include "../GamePackets/ChunkDataPacket.h"

TestMapManager* TestMapManager::pSingleton;

TestMapManager* TestMapManager::GetInstance() {
	if (!pSingleton) {
		pSingleton = new TestMapManager();
	}

	return pSingleton;
}

void TestMapManager::SendRegionAtPosition(ChunkPosition pos, Player* player) {
	Chunk testChunk;
	testChunk.SetPosition(pos);

	// Fill 16 chunk sections per chunk
	for (int i = 0; i < 10; i++) {
		ChunkSection section;

		// Fill 16 blocks per chunk section
		for (int j = 0; j < 4096; j++) {
			Block testBlock;
			testBlock.palette = 0b00000000010000;

			section.SetBlock(j, testBlock);
		}

		testChunk.SetSection(i, section);
	}

	ChunkDataPacket chunkMsg;
	chunkMsg.chunk = testChunk;

	player->GetNetClient()->Invoke(chunkMsg);
}
