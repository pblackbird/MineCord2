#pragma once

#include "Chunk.h"
#include "IMapManager.h"
#include "ChunkManager.h"

#define REGION_SIZE_IN_CHUNKS 3

class MapManager : public IMapManager {
DECLARE_SINGLETON(MapManager)

private:
	Logger logger;

public:
	MapManager() {
		logger.SetTag("Map manager");
	}

	virtual void OnChunkBorderCrossed(ChunkPosition newChunkPosition, ChunkPosition oldChunkPosition, Player* crosser) override;
	virtual void SendChunkAtPosition(ChunkPosition position, Player* player) override;
};