#pragma once

#include "IMapManager.h"
#include "../Player.h"

class TestMapManager : public IMapManager {
private:
	static TestMapManager* pSingleton;

public:
	static TestMapManager* GetInstance();

	virtual void SendRegionAtPosition(ChunkPosition pos, Player* player) override;
};