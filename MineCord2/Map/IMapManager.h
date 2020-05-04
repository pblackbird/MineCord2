#pragma once

#include "../Transformable.h"
#include "../ThirdParty/BufferedIO.h"
#include "Chunk.h"
#include "../Player.h"

/*
	Map manager that works with memory mapped map-data file will be implemented in future.
*/
class IMapManager {
public:
	// Serialize chunk at position
	virtual void SendRegionAtPosition(ChunkPosition pos, Player* player) = 0;
};