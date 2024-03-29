#pragma once

#include <functional>
#include <string>
#include <thread>
#include <map>
#include <algorithm>
#include <cassert>

#include "../MinecraftTypes.h"
#include "../Player.h"
#include "../Entities/Entity.h"
#include "../Logger.h"
#include "../GamePackets/SetPlayerTransformPacket.h"

class BaseWorld {
private:
	std::mutex _entityMutex;

protected:
	std::map<entity_id, Entity*> entities;
	std::vector<Player*> players;

protected:
	bool isWorldActive = true;

	std::thread worldTickThread;

	std::wstring name;

	int64_t tickRate = 120;

	Logger logger;

private:
	void PingPlayers();

public:
	BaseWorld() {
		logger.SetTag("World");
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

	bool DestroyEntity(entity_id id);
	void AddEntity(Entity* pEntity);

	bool DestroyPlayer(int networkId);
	PlayerEntity* AddPlayer(MinecraftNetworkClient* pClient, const std::string name, const std::string uuid);

	Player* GetPlayerBySlaveId(entity_id slaveId);
	Player* GetPlayerByNetworkClientId(int clientId);
	int GetPlayerIndexByNetworkClientId(int clientId);

	Entity* GetEntityByID(entity_id id);

	void EnumeratePlayers(std::function<void(Player* player)> callback);
	void EnumerateEntities(std::function<void(Entity * entity)> callback);

	void Run();
};