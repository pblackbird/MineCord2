#include "MapManager.h"
#include "../World/PrimaryWorld.h"
#include "../GamePackets/ChunkDataPacket.h"
#include "../GamePackets/UnloadChunkPacket.h"

MapManager* MapManager::pSingleton;

void MapManager::OnChunkBorderCrossed(ChunkPosition newChunkPosition, ChunkPosition oldChunkPosition, Player* crosser) {
	const auto chunkManager = ChunkManager::GetInstance();
	const auto world = PrimaryWorld::GetInstance();

	int chunkCrosslineLength = 2;

	for (int z = -chunkCrosslineLength; z < chunkCrosslineLength; z++) {
		for (int x = -chunkCrosslineLength; x < chunkCrosslineLength; x++) {
			ChunkPosition loadingChunkPosition = {
				newChunkPosition.x + x,
				newChunkPosition.z + z
			};

			SendChunkAtPosition(loadingChunkPosition, crosser);
		}
	}

	/*if (oldChunkPosition.x == newChunkPosition.x && oldChunkPosition.z == newChunkPosition.z) {
		return;
	}

	const auto xDiff = newChunkPosition.x - oldChunkPosition.x;
	const auto zDiff = newChunkPosition.z - oldChunkPosition.z;

	if (xDiff > chunkCrosslineLength || zDiff > chunkCrosslineLength) {
		auto oldChunk = chunkManager->GetChunkByPosition(oldChunkPosition);
		auto entityIdsInChunk = oldChunk->GetEntitiesInside();

		if (entityIdsInChunk.size() == 0) {
			chunkManager->DisposeChunk(oldChunkPosition);
		}

		UnloadChunkPacket unloadMsg;
		unloadMsg.x = oldChunkPosition.x;
		unloadMsg.z = oldChunkPosition.z;

		crosser->GetNetClient()->Invoke(unloadMsg);
	}*/
}

void MapManager::SendChunkAtPosition(ChunkPosition position, Player* player) {
	const auto chunkManager = ChunkManager::GetInstance();

	Chunk* playerChunk = chunkManager->GetChunkByPosition(
		position
	);

	if (!playerChunk) {
		playerChunk = chunkManager->LoadChunkFromDisk(position);
	}

	ChunkDataPacket chunkPkt;
	chunkPkt.chunk = playerChunk;
	
	player->GetNetClient()->Invoke(chunkPkt);
}
