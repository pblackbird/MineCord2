#include "Chunk.h"
#include "../MinecraftTypes.h"
#include "../NBT/NBTCompound.h"
#include "../NBT/NBTLongArray.h"
#include "../Utl.h"

void Chunk::Serialize(Buffer& dest) {
	NBTLongArray *test = new NBTLongArray();
	test->name = "MOTION_BLOCKING";
	
	// TODO: make heightmap building
	for (int i = 0; i < 36; i++) {
		test->array.push_back(0);
	}

	NBTCompound testHeightmap;
	testHeightmap.tags.push_back(test);
	
	dest.writeInt32_BE(x);
	dest.writeInt32_BE(z);
	dest.writeBool(true);
	
	uint16_t mask = 0b1111111111111111;
	MinecraftTypes::WriteVarInt(dest, mask);

	testHeightmap.Write(dest);
	
	MinecraftTypes::WriteVarInt(
		dest, 
		ChunkSection::GetSectionSizeInBytes(BITS_PER_BLOCK)
		* (sizeof(sections) / sizeof(ChunkSection))
	);

	for (int i = 0; i < sizeof(sections) / sizeof(ChunkSection); i++) {
		sections[i].Serialize(dest);
	}

	// no block entities on chunk synchronization
	MinecraftTypes::WriteVarInt(dest, 0);
}
