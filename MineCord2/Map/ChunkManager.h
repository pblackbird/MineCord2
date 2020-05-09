#pragma once

#include <map>
#include <thread>
#include <mutex>

#include "Chunk.h"
#include "../Utl.h"

#define CHUNK_MAP_HEIGHT 100000L
#define CHUNK_MAP_WIDTH 100000L

#define MAX_CHUNKS_IN_MEMORY CHUNK_MAP_WIDTH * CHUNK_MAP_HEIGHT

using ChunkMap = std::map<int32_t, Chunk*>;

class ChunkManager {
DECLARE_SINGLETON(ChunkManager)

private:
	ChunkMap loadedChunks;
	std::thread chunkDisposerThread;

	static std::mutex mutex;

public:
	static int32_t GetChunkID(ChunkPosition position);

	void RunDisposer();

	void DisposeUnusedChunks();

	bool DisposeChunk(ChunkPosition position);
	Chunk* LoadChunkFromDisk(ChunkPosition position);
	Chunk* GetChunkByPosition(ChunkPosition position);
};