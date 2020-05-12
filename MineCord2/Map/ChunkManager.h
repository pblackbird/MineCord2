#pragma once

#include <map>
#include <thread>
#include <mutex>

#include "Chunk.h"
#include "../Utl.h"

#define CHUNK_MAP_WIDTH 1000000L

using ChunkMap = std::map<int64_t, Chunk*>;

class ChunkManager {
DECLARE_SINGLETON(ChunkManager)

private:
	ChunkMap loadedChunks;
	std::thread chunkDisposerThread;

	static std::mutex mutex;

public:
	static int64_t GetChunkID(ChunkPosition position);

	bool DisposeChunk(ChunkPosition position);
	Chunk* LoadChunkFromDisk(ChunkPosition position);
	Chunk* GetChunkByPosition(ChunkPosition position);
};