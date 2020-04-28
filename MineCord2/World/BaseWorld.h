#pragma once

#include <string>
#include <thread>
#include <map>

#include "../Player.h"
#include "../Entities/Entity.h"
#include "../Logger.h"
#include "../GamePackets/SetPlayerTransformPacket.h"

class BaseWorld {
protected:
	std::map<ssize_t, Entity*> entities;
	std::vector<Player*> players;

protected:
	bool isWorldActive = true;

	std::thread worldTickThread;

	std::wstring name;

	int64_t tickRate = 120;

	Logger logger;

private:
	void SyncPlayers();

public:
	BaseWorld() {
		logger.SetTag(L"World");
	}

	virtual void Tick();

	void TickLoop();

	void SetTickRate(uint64_t tps) {
		tickRate = tps;
	}

	uint64_t GetTickRate() {
		return tickRate;
	}

	void BroadcastMessage(BaseNetPacket& msg, Player* me = nullptr);

	void AddEntity(Entity* pEntity);
	PlayerEntity* AddPlayer(MinecraftNetworkClient* pClient, const std::string&& name, const std::string&& uuid);

	Player* GetPlayerBySlaveId(entity_id slaveId);

	void Run();
};