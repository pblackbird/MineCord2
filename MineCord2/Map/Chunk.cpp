#include "Chunk.h"
#include "../MinecraftTypes.h"
#include "../NBT/NBTCompound.h"
#include "../NBT/NBTLongArray.h"
#include "../Utl.h"

void Chunk::Serialize(Buffer& dest) {
	// just testing
	NBTLongArray *test = new NBTLongArray();
	test->name = "MOTION_BLOCKING";
	
	for (int i = 0; i < 36; i++) {
		test->array.push_back(0);
	}

	NBTCompound testHeightmap;
	testHeightmap.tags.push_back(test);
	
	dest.writeInt32_BE(x);
	dest.writeInt32_BE(z);
	dest.writeBool(false); // todo: make full chunk support also
	
	uint16_t mask = 1;
	MinecraftTypes::WriteVarInt(dest, mask);

	testHeightmap.Write(dest);
	
	MinecraftTypes::WriteVarInt(dest, 0);
	//MinecraftTypes::WriteVarInt(dest, ChunkSection::GetSectionSizeInBytes(13));
	/*for (auto section : sections) {
		section.Serialize(dest);
	}*/

	MinecraftTypes::WriteVarInt(dest, 0);
}
