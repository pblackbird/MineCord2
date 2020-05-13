#include "TestMapGenerator.h"
#include "../Chunk.h"
#include "../MapDataFile.h"
#include "../ChunkManager.h"

void GenerateTestMap() {
	Logger generatorLogger("Map generator");

	generatorLogger.Info("Generating map ...");

	Chunk* testChunk = new Chunk();
	testChunk->SetPosition({ 1, 1 });

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

	int mapDataFd = open(MAP_FILE_PATH, O_RDWR | O_CREAT);

	MapDataFileHeader header;
	header.width = 1;
	header.height = 1;
	header.version = MAP_DATA_ENGINE_VERSION;

	write(mapDataFd, (MapDataFileHeader*)&header, sizeof(header));
	close(mapDataFd);

	MapDataFile mapData;
	mapData.WriteChunk(testChunk);

	generatorLogger.Info("Generated");
}
