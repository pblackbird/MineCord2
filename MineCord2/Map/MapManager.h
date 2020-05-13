#pragma once

#include "Chunk.h"
#include "IMapManager.h"
#include "ChunkManager.h"
#include "MapDataFile.h"

#define REGION_SIZE_IN_CHUNKS 5

class MapManager : public IMapManager {
DECLARE_SINGLETON(MapManager)

private:
	Logger logger;
	MapDataFile* mapData;

public:
	MapManager();

	void LoadMapData();

	bool Dispose(ChunkPosition position);

	virtual void OnChunkBorderCrossed(ChunkPosition newChunkPosition, ChunkPosition oldChunkPosition, Entity* crosser) override;
	virtual void SendChunkAtPosition(ChunkPosition position, Player* player) override;
};