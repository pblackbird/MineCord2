#pragma once

#include <cstdint>
#include <array>
#include <cmath>

#include "../Logger.h"
#include "../ThirdParty/BufferedIO.h"

#define BITS_PER_BLOCK 14

static Logger logger("Chunk section manager");

typedef struct {
	int64_t palette;
} Block;

class ChunkSection {
private:
	Block blocks[4096];

public:
	void Serialize(Buffer& dest);
	uint16_t GetBlockEntityCount();

	Block GetBlock(uint32_t index) {
		return blocks[index];
	}

	void SetBlock(uint32_t index, Block block) {
		blocks[index] = block;
	}

	constexpr static uint32_t GetSectionSizeInBytes(uint8_t bitsPerBlock) {
		return (uint32_t)(
			sizeof(uint16_t) +
			sizeof(uint8_t) + 
			2 +
			GetLongsCount(bitsPerBlock) * sizeof(uint64_t)
		);
	}

	constexpr static uint32_t GetLongsCount(uint8_t bitsPerBlock) {
		const auto totallyBitsForBlocks = 4096 * bitsPerBlock;
		const auto totallyLongsForBlocks = (int)std::ceil((double)totallyBitsForBlocks / 64.0);

		return totallyLongsForBlocks;
	}
};