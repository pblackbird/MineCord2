#include "ChunkManager.h"

ChunkManager* ChunkManager::pSingleton;

int64_t ChunkManager::GetChunkID(ChunkPosition position) {
	return (int64_t)((position.z * CHUNK_MAP_WIDTH) + position.x);
}

bool ChunkManager::DisposeChunk(ChunkPosition position) {
	auto chunk = GetChunkByPosition(position);

	if (!chunk) {
		return false;
	}

	loadedChunks.erase(chunk->GetID());
	delete chunk;

	return true;
}

Chunk* ChunkManager::LoadChunkFromDisk(ChunkPosition position, MapDataFile* mapData) {
	if (GetChunkByPosition(position)) {
		return nullptr;
	}

	Chunk* pChunk = mapData->ReadChunk(position);

	if (!pChunk) {
		return nullptr;
	}

	loadedChunks[ChunkManager::GetChunkID(position)] = pChunk;

	return pChunk;
}

Chunk* ChunkManager::GetChunkByPosition(ChunkPosition position) {
	return loadedChunks[ChunkManager::GetChunkID(position)];
}
