#include "ChunkSection.h"
#include "../MinecraftTypes.h"

uint32_t ChunkSection::GetLongsCount(uint8_t bitsPerBlock) {
	const auto totallyBitsForBlocks = 4096 * bitsPerBlock;
	const auto totallyLongsForBlocks = (int)std::ceil((double)totallyBitsForBlocks / 64.0);

	return totallyLongsForBlocks;
}

void ChunkSection::Serialize(Buffer& dest) {
	const auto blockEntitiyCount = GetBlockEntityCount();

	dest.writeUInt16_BE(blockEntitiyCount);
	dest.writeUInt8(bitsPerBlock); // 14 bits per block for testing only to use global palette

	// serialize blocks
	const auto totallyLongsForBlocks = GetLongsCount(bitsPerBlock);
	
	MinecraftTypes::WriteVarInt(dest, totallyLongsForBlocks);

	// ...
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
	return sizeof(uint16_t) + sizeof(uint8_t) + 2 + GetLongsCount(bitsPerBlock) * sizeof(uint64_t);
}
