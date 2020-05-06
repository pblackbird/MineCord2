#include "BaseWorld.h"
#include "../Entities/PlayerEntity.h"
#include "../GamePackets/SetPlayerTransformPacket.h"
#include "../GamePackets/JoinGamePacket.h"
#include "../Network/NetConfig.h"

void BaseWorld::PingPlayers() {
	const auto pingingTime = std::time(NULL);

	for (const auto player : players) {
		if ((pingingTime - player->GetLastPing()) < 10) {
			continue;
		}

		if ((pingingTime - player->GetLastPing()) > CONNECTION_KEEPALIVE_SECONDS && player->IsWaitingForPong()) {
			player->GetNetClient()->Disconnect();
			continue;
		}

		player->Ping();
	}
}

void BaseWorld::Tick() {
	std::lock_guard<std::mutex> lock(_entityMutex);

	for (std::map<ssize_t, Entity*>::iterator i = entities.begin(); i != entities.end(); i++) {
		i->second->OnTick();
	}
}

void BaseWorld::TickLoop() {
	auto tickTimerStart = std::chrono::high_resolution_clock::now();
	ssize_t currentTPS = 0;

	while (isWorldActive) {
		Tick();
		currentTPS++;

		usleep((uint32_t)((1000.0 / (double)tickRate)));

		const auto tickTimerFinish = std::chrono::high_resolution_clock::now();
		const auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
			tickTimerFinish - tickTimerStart
		).count();

		if (elapsed >= 1000) {
			PingPlayers();

			if (currentTPS < tickRate) {
				logger.Warning("Current TPS (%llu) is less than %llu", currentTPS, tickRate);
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

	delete entities[id];
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

	delete players[playerIndex];
	players.erase(players.begin() + playerIndex);

	return true;
}

PlayerEntity* BaseWorld::AddPlayer(MinecraftNetworkClient* pClient, const std::string name, const std::string uuid) {
	auto player = new Player(pClient);
	auto playerEntity = new PlayerEntity(uuid);

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
	for (size_t i = 0; i < players.size(); i++) {
		if (players[i]->GetNetClient()->GetNetID() != clientId) {
			continue;
		}

		return (int)i;
	}

	return -1;
}

void BaseWorld::EnumeratePlayers(std::function<void(Player* player)> callback) {
	for (Player* player : this->players) {
		callback(player);
	}
}

void BaseWorld::Run() {
	worldTickThread = std::thread(_threadEntry, this);
}
