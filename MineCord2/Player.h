#pragma once

#include <memory>
#include <map>

#include "Network/MinecraftNetworkClient.h"
#include "Entities/PlayerEntity.h"

class Player;

typedef void(*OnPlayerAction_t)(Player*, BaseNetPacket&);

class Player {
private:
	PlayerEntity* pSlave;
	MinecraftNetworkClient* pNetClient;

public:
	Player(MinecraftNetworkClient* pClient) {
		pNetClient = pClient;
	}

	~Player();

	void Join();
	void SetTransform(Point3D position, Angle rotation, int teleportId = 0);
	void OnMsg(BaseNetPacket& msg);

	void SetSlaveEntity(PlayerEntity* pEnt) {
		pSlave = pEnt;
	}

	PlayerEntity* GetSlaveEntity() {
		return pSlave;
	}

	MinecraftNetworkClient* GetNetClient() {
		return pNetClient;
	}
};