#pragma once

#include <memory>
#include <map>
#include <ctime>

#include "GamePackets/PlayerInfoPacket.h"
#include "Network/MinecraftNetworkClient.h"
#include "Entities/PlayerEntity.h"
#include "Map/Chunk.h"

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
	void Join(GameMode mode);
	void SetTransform(Point3D position, Angle rotation, int teleportId = 0);

	void SetPlayerPositionChunk(ChunkPosition chunkPos);
	
	void Ping();

public:
	Player(MinecraftNetworkClient* pClient) {
		pNetClient = pClient;
		lastKeepAlive = std::time(NULL);
		playerLogger.SetTag(pClient->GetUsername());
	}

	~Player();

	std::string GetUsername() {
		return pNetClient->GetUsername();
	}

	void OnMsg(BaseNetPacket& msg);

	void ControlTabMenu(PlayerInfoAction action, std::vector<PlayerListEntry> players);
	void SpawnVisiblePlayer(Player* visiblePlayer);
	void UnloadChunk(ChunkPosition position);
	void LoadChunk(Chunk* pChunk);

	void AnnounceNewRegion(ChunkPosition newRegionOrigin, ChunkPosition oldRegionOrigin);
	void DisposeOldRegion(ChunkPosition newRegionOrigin, ChunkPosition oldRegionOrigin);

	void OnChunkBorderCrossed(ChunkPosition newRegionOrigin, ChunkPosition oldRegionOrigin);

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