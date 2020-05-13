#include "MapManager.h"
#include "../World/PrimaryWorld.h"

MapManager* MapManager::pSingleton;

MapManager::MapManager() {
	logger.SetTag("Map manager");
}

void MapManager::LoadMapData() {
	mapData = new MapDataFile();
}

bool MapManager::Dispose(ChunkPosition position) {
	const auto chunkManager = ChunkManager::GetInstance();

	Chunk* pChunk = chunkManager->GetChunkByPosition(position);

	if (!pChunk) {
		return false;
	}

	if (pChunk->GetEntitiesInside().size() != 0) {
		return false;
	}

	chunkManager->DisposeChunk(position);

	return true;
}

void MapManager::OnChunkBorderCrossed(ChunkPosition newChunkPosition, ChunkPosition oldChunkPosition, Entity* crosser) {
	const auto chunkManager = ChunkManager::GetInstance();
	const auto world = PrimaryWorld::GetInstance();

	if (!crosser->IsPlayer()) {
		return;
	}

	Player* crosserPlayer = world->GetPlayerBySlaveId(crosser->GetID());
	crosserPlayer->SetPlayerPositionChunk(newChunkPosition);

	crosserPlayer->OnChunkBorderCrossed(newChunkPosition, oldChunkPosition);
}

void MapManager::SendChunkAtPosition(ChunkPosition position, Player* player) {
	const auto chunkManager = ChunkManager::GetInstance();

	Chunk* playerChunk = chunkManager->GetChunkByPosition(
		position
	);

	if (!playerChunk) {
		playerChunk = chunkManager->LoadChunkFromDisk(position, mapData);

		if (!playerChunk) {
			logger.Warning(
				"Chunk at position %i %i could not be loaded!",
				position.x,
				position.z
			);

			return;
		}
	}

	player->LoadChunk(playerChunk);
}
