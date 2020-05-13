#include "TestMapGenerator.h"
#include "../Chunk.h"
#include "../MapDataFile.h"
#include "../ChunkManager.h"

void GenerateTestMap() {
	Logger generatorLogger("Map generator");

	generatorLogger.Info("Generating map ...");

	Chunk* testChunk = new Chunk();

	for (int i = 0; i < 12; i++) {
		ChunkSection section = {};

		for (int j = 0; j < 4096; j++) {
			Block testBlock;
			testBlock.palette = 1;//0b00000000010000;

			section.SetBlock(j, testBlock);
		}

		testChunk->SetSection(i, section);
	}

	int mapDataFd = open(MAP_FILE_PATH, O_RDWR | O_CREAT);

	MapDataFileHeader header;
	header.width = CHUNK_MAP_WIDTH;
	header.height = CHUNK_MAP_WIDTH;
	header.version = MAP_DATA_ENGINE_VERSION;

	const auto dataSize = sizeof(MapDataFileHeader) + sizeof(ChunkDataEntry) * CHUNK_MAP_WIDTH * CHUNK_MAP_WIDTH;
	char* dataBuf = new char[dataSize];

	bzero(dataBuf, dataSize);
	memcpy(dataBuf, (MapDataFileHeader*)&header, sizeof(header));

	write(mapDataFd, dataBuf, dataSize);
	close(mapDataFd);

	for (int x = 0; x < CHUNK_MAP_WIDTH; x++) {
		for (int z = 0; z < CHUNK_MAP_WIDTH; z++) {
			MapDataFile mapData;
			testChunk->SetPosition({ x, z });
			mapData.WriteChunk(testChunk);
		}
	}

	delete dataBuf;
	delete testChunk;

	generatorLogger.Info("Generated");
}
