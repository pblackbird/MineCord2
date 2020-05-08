#pragma once

#include <cmath>
#include <cassert>
#include <strings.h>
#include <functional>

#include "ChunkSection.h"
#include "../Transformable.h"
#include "../ThirdParty/BufferedIO.h"

class Chunk;

typedef struct {
	int32_t x, z;
} ChunkPosition;

using OnChunkBlockChanged_t = std::function<void (Chunk*, Block)>;

/*
	16x256x16 chunk
*/

class Chunk {
private:
	int32_t x, z;
	ChunkSection sections[16];
	OnChunkBlockChanged_t blockChangedCallback = nullptr;

public:
	void Serialize(Buffer& dest);

	void SetBlockChangedCallback(OnChunkBlockChanged_t callback) {
		blockChangedCallback = callback;
	}

	void SetBlock(Block block, Point3D position);
	Block GetBlock(Point3D position);
		
	void SetPosition(ChunkPosition pos) {
		x = pos.x;
		z = pos.z;
	}

	ChunkSection GetSection(uint32_t index) {
		return sections[index];
	}

	void SetSection(uint32_t index, ChunkSection section) {
		sections[index] = section;
	}

	ChunkPosition GetPosition() {
		return { x, z };
	}
};