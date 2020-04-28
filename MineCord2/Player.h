#pragma once

#include <memory>

#include "Network/MinecraftNetworkClient.h"
#include "Entities/PlayerEntity.h"

class Player {
private:
	PlayerEntity* pSlave;
	MinecraftNetworkClient* pNetClient;

public:
	Player(MinecraftNetworkClient* pClient) {
		pNetClient = pClient;
	}

	void SetSlaveEntity(PlayerEntity* pEnt) {
		pSlave = pEnt;
	}

	PlayerEntity* GetSlaveEntity() {
		return pSlave;
	}

	MinecraftNetworkClient* GetNetClient() {
		return pNetClient;
	}

	void Join();
	void SetTransform(Point3D position, Angle rotation, int teleportId = 0);
};