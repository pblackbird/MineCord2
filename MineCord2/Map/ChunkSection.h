#pragma once

#include <cstdint>
#include <array>
#include <cmath>

#include "../Logger.h"
#include "../ThirdParty/BufferedIO.h"

static Logger logger(L"Chunk section manager");

typedef struct {
	uint32_t palette;
} Block;

class ChunkSection {
private:
	Block blocks[4096];
	uint8_t bitsPerBlock = 13;

public:
	void Serialize(Buffer& dest);
	uint16_t GetBlockEntityCount();

	Block GetBlock(uint32_t index) {
		return blocks[index];
	}

	void SetBlock(uint32_t index, Block block) {
		blocks[index] = block;
	}

	static uint32_t GetSectionSizeInBytes(uint8_t bitsPerBlock);
	static uint32_t GetLongsCount(uint8_t bitsPerBlock);
};