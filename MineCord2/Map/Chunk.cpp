#include "Chunk.h"
#include "../MinecraftTypes.h"
#include "../NBT/NBTCompound.h"
#include "../NBT/NBTLongArray.h"
#include "../World/PrimaryWorld.h"
#include "../Utl.h"
#include "../Map/ChunkManager.h"

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
		ChunkSection::GetSectionSizeInBytes(BITS_PER_BLOCK) * (int)(sizeof(sections) / sizeof(ChunkSection))
		+ 256 * sizeof(uint32_t)
	);

	for (int i = 0; i < (int)(sizeof(sections) / sizeof(ChunkSection)); i++) {
		sections[i].Serialize(dest);
	}

	// no block entities on chunk synchronization
	MinecraftTypes::WriteVarInt(dest, 0);

	// todo: implement biome data
	for (int i = 0; i < 256; i++) {
		dest.writeInt32_BE(0);
	}
}

void Chunk::SetBlock(Block block, Point3D position) {
	if (position.y >= 256.f) {
		return;
	}

	const int sectionIndex = (int)position.y / 16;

	ChunkSection section = sections[sectionIndex];

	int blockIndex = section.BlockRelativePositionToIndex({
		position.x,
		(float)((int)position.y % 16),
		position.z
	});
		
	sections[sectionIndex].SetBlock(blockIndex, block);

	if (blockChangedCallback) {
		blockChangedCallback(this, block);
	}
}

Block Chunk::GetBlock(Point3D position) {
	if (position.y >= 256.f) {
		return AIR_BLOCK;
	}

	ChunkSection section = sections[(int)position.y / 16];

	return section.GetBlock(section.BlockRelativePositionToIndex({
		position.x,
		(float)((int)position.y % 16),
		position.z
	}));
}

std::vector<entity_id> Chunk::GetEntitiesInside() {
	const auto world = PrimaryWorld::GetInstance();
	std::vector<entity_id> result;

	const auto thisChunkPosition = this->GetPosition();

	world->EnumerateEntities([&result, thisChunkPosition](Entity* entity) {
		const auto entityChunkPosition = entity->GetCurrentChunkPosition();

		bool xmatch = entityChunkPosition.x == thisChunkPosition.x;
		bool zmatch = entityChunkPosition.z == thisChunkPosition.z;

		if (xmatch && zmatch) {
			result.push_back(entity->GetID());
		}
	});

	return result;
}

int32_t Chunk::GetID() {
	return ChunkManager::GetChunkID({ x, z });
}
