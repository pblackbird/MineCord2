#include "ChunkSection.h"
#include "../MinecraftTypes.h"

uint32_t ChunkSection::GetLongsCount(uint8_t bitsPerBlock) {
	const auto totallyBitsForBlocks = 4096 * bitsPerBlock;
	const auto totallyLongsForBlocks = (int)std::ceil((double)totallyBitsForBlocks / 64.0);

	return totallyLongsForBlocks;
}

void ChunkSection::Serialize(Buffer& dest) {
	const auto blockEntitiyCount = GetBlockEntityCount();

	dest.writeInt16_BE(blockEntitiyCount);
	dest.writeUInt8(BITS_PER_BLOCK); // 13 bits per block
	dest.writeUInt8(0); // no custom palette

	// serialize blocks
	MinecraftTypes::WriteVarInt(dest, GetLongsCount(BITS_PER_BLOCK));
	
	uint64_t currentLong = 0;
	int bitsWrittenAtEntry = 0;

	for (int i = 0; i < (int)(sizeof(blocks) / sizeof(Block)); i++) {
		Block block = blocks[i];

		for (int bit = 0; bit < BITS_PER_BLOCK; bit++) {
			currentLong |= (((1 << bit) & block.palette) >> bit);
			bitsWrittenAtEntry++;

			if (bitsWrittenAtEntry == 64) {
				dest.writeInt64_BE(currentLong);

				currentLong = 0;
				bitsWrittenAtEntry = 0;
			}
		}
	}

	if (currentLong != 0) {
		dest.writeInt64_BE(currentLong);
	}
}

uint16_t ChunkSection::GetBlockEntityCount() {
	uint16_t nonAirBlocks = 0;

	for (auto block : blocks) {
		if (block.palette > 0) {
			nonAirBlocks++;
		}
	}

	return nonAirBlocks;
}

uint32_t ChunkSection::GetSectionSizeInBytes(uint8_t bitsPerBlock) {
	return (uint32_t)(
		sizeof(uint16_t) + 
		sizeof(uint8_t) + 
		sizeof(uint8_t) + 
		2 +
		GetLongsCount(bitsPerBlock) * sizeof(uint64_t)
	);
}
