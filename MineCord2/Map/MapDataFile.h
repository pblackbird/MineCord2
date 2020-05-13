#pragma once

#include "Chunk.h"
#include "../MemoryMappedFile.h"

#define MAP_FILE_PATH "./game_map.dat"
#define MAP_DATA_ENGINE_VERSION 1

typedef struct {
	uint32_t version;
	uint64_t width;
	uint64_t height;
} MapDataFileHeader;

typedef struct {
	ChunkSection sections[16];
} ChunkDataEntry;

class MapDataFile {
private:
	MemoryMappedFile* pMemoryMappedFile;
	Logger logger;

	MapDataFileHeader* headers;
	ChunkDataEntry* chunks;

private:
	int64_t GetChunkIndex(ChunkPosition position);
	int64_t GetMaxChunkIndex();

public:
	MapDataFile();
	~MapDataFile();

	Chunk* ReadChunk(ChunkPosition position);
	bool WriteChunk(Chunk* chunk);
};