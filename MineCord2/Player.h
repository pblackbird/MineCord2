#pragma once

#include <memory>
#include <map>
#include <ctime>

#include "Network/MinecraftNetworkClient.h"
#include "Entities/PlayerEntity.h"

class Player;

typedef void(*OnPlayerAction_t)(Player*, BaseNetPacket&);

class Player {
private:
	PlayerEntity* pSlave;
	MinecraftNetworkClient* pNetClient;

	uint64_t lastKeepAlive = 0;
	bool isWaitingForPong = false;

	Logger playerLogger;

private:
	void DispatchServiceMessage(BaseNetPacket& msg);

public:
	void Join();
	void SetTransform(Point3D position, Angle rotation, int teleportId = 0);
	
	void Ping();

public:
	Player(MinecraftNetworkClient* pClient) {
		pNetClient = pClient;
		lastKeepAlive = std::time(NULL);
		playerLogger.SetTag(pClient->GetUsername());
	}

	~Player();

	void OnMsg(BaseNetPacket& msg);

	void SetSlaveEntity(PlayerEntity* pEnt) {
		pSlave = pEnt;
	}

	bool IsWaitingForPong() {
		return isWaitingForPong;
	}

	uint64_t GetLastPing() {
		return lastKeepAlive;
	}

	PlayerEntity* GetSlaveEntity() {
		return pSlave;
	}

	MinecraftNetworkClient* GetNetClient() {
		return pNetClient;
	}
};