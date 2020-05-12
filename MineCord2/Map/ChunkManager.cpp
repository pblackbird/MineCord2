#include "ChunkManager.h"

ChunkManager* ChunkManager::pSingleton;

int64_t ChunkManager::GetChunkID(ChunkPosition position) {
	return (int64_t)((position.z * CHUNK_MAP_WIDTH) + position.x);
}

bool ChunkManager::DisposeChunk(ChunkPosition position) {
	logger.Info("Disposing chunk at %i %i ...", position.x, position.z);

	auto chunk = GetChunkByPosition(position);

	if (!chunk) {
		return false;
	}

	loadedChunks.erase(chunk->GetID());
	delete chunk;

	return true;
}

Chunk* ChunkManager::LoadChunkFromDisk(ChunkPosition position) {
	if (GetChunkByPosition(position)) {
		return nullptr;
	}

	// TODO: implement memory mapped file
	Chunk *testChunk = new Chunk();
	testChunk->SetPosition(position);

	// Fill 16 chunk sections per chunk
	for (int i = 0; i < 12; i++) {
		ChunkSection section = {};

		// Fill 16 blocks per chunk section
		for (int j = 0; j < 4096; j++) {
			Block testBlock;
			testBlock.palette = 0b00000000010000;

			section.SetBlock(j, testBlock);
		}

		testChunk->SetSection(i, section);
	}

	for (int x = 0; x < 16; x++) {
		for (int z = 0; z < 16; z++) {
			testChunk->SetBlock(Block(0b00000011010000), {
				(double)x,
				255 - 4 * 16,
				(double)z
			});
		}
	}

	loadedChunks[ChunkManager::GetChunkID(position)] = testChunk;

	return testChunk;
}

Chunk* ChunkManager::GetChunkByPosition(ChunkPosition position) {
	return loadedChunks[ChunkManager::GetChunkID(position)];
}
