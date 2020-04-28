#include "BaseWorld.h"
#include "../Entities/PlayerEntity.h"
#include "../GamePackets/SetPlayerTransformPacket.h"
#include "../GamePackets/JoinGamePacket.h"

void BaseWorld::SyncPlayers() {
	for (const auto player : players) {
		
	}
}

void BaseWorld::Tick() {
	std::lock_guard<std::mutex> lock(_entityMutex);

	for (std::map<ssize_t, Entity*>::iterator i = entities.begin(); i != entities.end(); i++) {
		i->second->OnTick();
	}

	SyncPlayers();
}

void BaseWorld::TickLoop() {
	auto tickTimerStart = std::chrono::high_resolution_clock::now();
	ssize_t currentTPS = 0;

	while (isWorldActive) {
		if (currentTPS <= tickRate) {
			Tick();
			currentTPS++;
		}

		const auto tickTimerFinish = std::chrono::high_resolution_clock::now();
		const auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(
			tickTimerFinish - tickTimerStart
		).count();

		if (elapsed == 1) {
			if (currentTPS < tickRate) {
				logger.Warning(L"Current TPS (%llu) is less than %llu", currentTPS, tickRate);
			}

			currentTPS = 0;
			tickTimerStart = std::chrono::high_resolution_clock::now();
		}
	}
}

void _threadEntry(BaseWorld* pWorld) {
	pWorld->TickLoop();
}

void BaseWorld::BroadcastMessage(BaseNetPacket& msg, Player* me) {
	for (const auto player : players) {
		if (me && me == player) {
			continue;
		}

		player->GetNetClient()->Invoke(msg);
	}
}

bool BaseWorld::DestroyEntity(entity_id id) {
	std::lock_guard<std::mutex> lock(_entityMutex);

	if (!entities[id]) {
		return false;
	}

	entities[id]->OnDestroy();
	entities.erase(id);

	return true;
}

void BaseWorld::AddEntity(Entity* pEntity) {
	std::lock_guard<std::mutex> lock(_entityMutex);

	entities[pEntity->GetID()] = pEntity;
	pEntity->OnCreate();
}

bool BaseWorld::DestroyPlayer(int networkId) {
	int playerIndex = GetPlayerIndexByNetworkClientId(networkId);
	if (playerIndex < 0) {
		return false;
	}

	players.erase(players.begin() + playerIndex);

	return true;
}

PlayerEntity* BaseWorld::AddPlayer(MinecraftNetworkClient* pClient, const std::string&& name, const std::string&& uuid) {
	auto player = new Player(pClient);
	auto playerEntity = new PlayerEntity(std::move(uuid));

	playerEntity->SetName(name);
	player->SetSlaveEntity(playerEntity);

	players.push_back(player);

	AddEntity(playerEntity);

	return playerEntity;
}

Player* BaseWorld::GetPlayerBySlaveId(entity_id slaveId) {
	for (const auto player : players) {
		if (player->GetSlaveEntity()->GetID() != slaveId) {
			continue;
		}

		return player;
	}

	return nullptr;
}

Player* BaseWorld::GetPlayerByNetworkClientId(int clientId) {
	for (const auto player : players) {
		if (player->GetNetClient()->GetNetID() != clientId) {
			continue;
		}

		return player;
	}

	return nullptr;
}

int BaseWorld::GetPlayerIndexByNetworkClientId(int clientId) {
	for (int i = 0; i < players.size(); i++) {
		if (players[i]->GetNetClient()->GetNetID() != clientId) {
			continue;
		}

		return i;
	}

	return -1;
}

void BaseWorld::Run() {
	worldTickThread = std::thread(_threadEntry, this);
}
