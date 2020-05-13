#include "MapDataFile.h"
#include "ChunkManager.h"

int64_t MapDataFile::GetChunkIndex(ChunkPosition position) {
	const int64_t chunkIndex = ChunkManager::GetChunkID(position);
	const int64_t maxChunkIndex = GetMaxChunkIndex();

	if (chunkIndex > maxChunkIndex) {
		logger.Warning("Chunk index %i was requested, max chunk index: %i", chunkIndex, maxChunkIndex);
		return -1;
	}

	return chunkIndex;
}

int64_t MapDataFile::GetMaxChunkIndex() {
	return headers->width * headers->height;
}

MapDataFile::MapDataFile() {
	logger.SetTag("Map data manager");

	pMemoryMappedFile = new MemoryMappedFile(MAP_FILE_PATH);
	
	const auto fSize = sizeof(MapDataFileHeader) + sizeof(ChunkDataEntry) * 100 * 100;

	if (!pMemoryMappedFile->Open(fSize)) {
		logger.Error("Error opening map data file: %i", errno);
		exit(1);
	}

	const auto data = pMemoryMappedFile->GetPointer();

	headers = (MapDataFileHeader*)data;

	if (headers->version != MAP_DATA_ENGINE_VERSION) {
		logger.Error(
			"Map data version mismatch. %i expected, but got %i",
			MAP_DATA_ENGINE_VERSION,
			headers->version
		);

		exit(1);
	}

	chunks = (ChunkDataEntry*)((uintptr_t)data + sizeof(MapDataFile));
}

MapDataFile::~MapDataFile() {
	delete pMemoryMappedFile;
}

Chunk* MapDataFile::ReadChunk(ChunkPosition position) {
	const auto chunkIndex = GetChunkIndex(position);
	if (chunkIndex < 0) {
		return nullptr;
	}

	ChunkDataEntry chunkData = chunks[chunkIndex];

	Chunk* pChunk = new Chunk();
	pChunk->SetPosition(position);

	for (int i = 0; i < 16; i++) {
		pChunk->SetSection(i, chunkData.sections[i]);
	}

	return pChunk;
}

bool MapDataFile::WriteChunk(Chunk* chunk) {
	const auto chunkIndex = GetChunkIndex(chunk->GetPosition());
	if (chunkIndex < 0) {
		return false;
	}
	

	for (int i = 0; i < 16; i++) {
		chunks[chunkIndex].sections[i] = chunk->GetSection(i);
	}

	return true;
}
