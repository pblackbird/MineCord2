#include "MapManager.h"
#include "../World/PrimaryWorld.h"
#include "../GamePackets/ChunkDataPacket.h"

MapManager* MapManager::pSingleton;

void MapManager::OnChunkBorderCrossed(ChunkPosition newChunkPosition, Player* crosser) {
	int chunkCrosslineLength = (int)std::sqrt(REGION_SIZE_IN_CHUNKS);

	logger.Info(
		"%s crossed chunk border. New chunk - (%i %i)", 
		crosser->GetUsername().c_str(),
		newChunkPosition.x,
		newChunkPosition.z
	);

	for (int z = -chunkCrosslineLength; z < chunkCrosslineLength; z++) {
		for (int x = -chunkCrosslineLength; x < chunkCrosslineLength; x++) {
			ChunkPosition loadingChunkPosition = {
				newChunkPosition.x + x,
				newChunkPosition.z + z
			};

			SendChunkAtPosition(loadingChunkPosition, crosser);
		}
	}
}

void MapManager::SendChunkAtPosition(ChunkPosition position, Player* player) {
	const auto chunkManager = ChunkManager::GetInstance();

	Chunk* playerChunk = chunkManager->GetChunkByPosition(
		position
	);

	if (!playerChunk) {
		logger.Info(
			"Chunk at position %i %i is not loaded! Loading it from disk ...", 
			position.x,
			position.z
		);

		playerChunk = chunkManager->LoadChunkFromDisk(position);
	}

	ChunkDataPacket chunkPkt;
	chunkPkt.chunk = playerChunk;
	
	player->GetNetClient()->Invoke(chunkPkt);
}
