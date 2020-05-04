#pragma once

#include <cmath>
#include <cassert>
#include <strings.h>

#include "ChunkSection.h"
#include "../ThirdParty/BufferedIO.h"

typedef struct {
	uint32_t x, z;
} ChunkPosition;

/*
	16x256x16 chunk
*/

class Chunk {
private:
	uint32_t x, z;
	ChunkSection sections[16];

public:
	void Serialize(Buffer& dest);

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