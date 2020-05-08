#pragma once

#include "Chunk.h"
#include "IMapManager.h"
#include "ChunkManager.h"

#define REGION_SIZE_IN_CHUNKS 4

class MapManager : public IMapManager {
DECLARE_SINGLETON(MapManager)

private:
	Logger logger;

public:
	MapManager() {
		logger.SetTag("Map manager");
	}

	virtual void OnChunkBorderCrossed(ChunkPosition newChunkPosition, Player* crosser) override;
	virtual void SendChunkAtPosition(ChunkPosition position, Player* player) override;
};