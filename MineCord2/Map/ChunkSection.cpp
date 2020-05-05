#include "ChunkSection.h"
#include "../MinecraftTypes.h"

void ChunkSection::Serialize(Buffer& dest) {
	const auto blockEntitiyCount = GetBlockEntityCount();

	dest.writeInt16_BE(blockEntitiyCount);
	dest.writeUInt8(BITS_PER_BLOCK); // 14 bits per block

	// serialize blocks
	MinecraftTypes::WriteVarInt(dest, GetLongsCount(BITS_PER_BLOCK));

	uint64_t longs[GetLongsCount(BITS_PER_BLOCK)];

	for (int i = 0; i < (int)(sizeof(blocks) / sizeof(Block)); i++) {
		Block block = blocks[i];

		int64_t beginOverlap = (i * BITS_PER_BLOCK) / 64;
		int64_t off = (i * BITS_PER_BLOCK) % 64;
		int64_t endOverlap = ((i + 1) * BITS_PER_BLOCK - 1) / 64;

		int64_t blockIdentity = block.palette;

		longs[beginOverlap] |= (blockIdentity << off);

		if (beginOverlap != endOverlap) {
			longs[endOverlap] = (blockIdentity >> (64 - off));
		}
	}

	for (int i = 0; i < (int)GetLongsCount(BITS_PER_BLOCK); i++) {
		dest.writeInt64_BE(longs[i]);
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
