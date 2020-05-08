#pragma once

#include "Chunk.h"
#include "../Transformable.h"
#include "../ThirdParty/BufferedIO.h"
#include "../Player.h"

/*
	Map manager that works with memory mapped map-data file will be implemented in future.
*/
class IMapManager {
public:
	virtual void OnChunkBorderCrossed(ChunkPosition crossedChunkPosition, Player* crosser) = 0;
	virtual void SendChunkAtPosition(ChunkPosition pos, Player* player) = 0;
};