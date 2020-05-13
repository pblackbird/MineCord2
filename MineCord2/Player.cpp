#include "Player.h"
#include "GamePackets/JoinGamePacket.h"
#include "GamePackets/KeepAlivePacket.h"
#include "GamePackets/SetPlayerTransformPacket.h"
#include "GamePackets/UpdateViewPositionPacket.h"
#include "GamePackets/UnloadChunkPacket.h"
#include "GamePackets/ChunkDataPacket.h"

#include "World/PrimaryWorld.h"
#include "Map/MapManager.h"

#include "PlayerActions/PlayerMove.h"
#include "PlayerActions/ChatMsg.h"
#include "GamePackets/SpawnPlayerPacket.h"
#include <string.h>

static std::map<int, OnPlayerAction_t> playerActionHandlers = {
	{ CHAT_MSG_FROM_CLIENT_PACKETID, OnPlayerChatMessage },

	{ SYNC_PLAYER_CLIENT, OnPlayerMove },
	{ SYNC_PLAYER_CLIENT_ROTATION_POSITION, OnPlayerMove },
	{ SYNC_PLAYER_CLIENT_ROTATION, OnPlayerMove }
};

Player::~Player() {
	PrimaryWorld::GetInstance()->DestroyEntity(
		pSlave->GetID()
	);
}

void Player::DispatchServiceMessage(BaseNetPacket& msg) {
	switch (msg.packetId) {
		case KEEP_ALIVE_CLIENT_PACKETID: {
			if (!isWaitingForPong) {
				return;
			}

			isWaitingForPong = false;
			lastKeepAlive = std::time(NULL);

			break;
		}
	}
}

void Player::Join(GameMode mode) {
	JoinGamePacket join;
	join.entityId = pSlave->GetID();
	join.gamemode = mode;
	join.dimension = Dimension::OVERWORLD;
	join.maxPlayers = 100;
	join.worldType = "default";
	join.viewDistance = 10;
	join.isDebug = false;

	pNetClient->Invoke(join);
}

void Player::SetTransform(Point3D position, Angle rotation, int teleportId) {
	SetPlayerTransformPacket transformMsg;
	transformMsg.flags = 0;
	transformMsg.teleportId = teleportId;

	transformMsg.pitch = rotation.pitch;
	transformMsg.yaw = rotation.yaw;

	transformMsg.x = position.x;
	transformMsg.y = position.y;
	transformMsg.z = position.z;

	pNetClient->Invoke(transformMsg);
}

void Player::SetPlayerPositionChunk(ChunkPosition chunkPos) {
	UpdateViewPositionPacket updateViewPos;
	updateViewPos.chunkX = chunkPos.x;
	updateViewPos.chunkZ = chunkPos.z;

	pNetClient->Invoke(updateViewPos);
}

void Player::Ping() {
	KeepAlivePacket keepAliveMsg;
	keepAliveMsg.keepAliveId = std::time(NULL);

	pNetClient->Invoke(keepAliveMsg);

	isWaitingForPong = true;
}

void Player::OnMsg(BaseNetPacket& msg) {
	DispatchServiceMessage(msg);

	if (!playerActionHandlers[msg.packetId]) {
		return;
	}

	playerActionHandlers[msg.packetId](this, msg);
}

void Player::ControlTabMenu(PlayerInfoAction action, std::vector<PlayerListEntry> players) {
	PlayerInfoPacket infoPacket;
	infoPacket.action = action;
	infoPacket.players = players;

	pNetClient->Invoke(infoPacket);
}

void Player::SpawnVisiblePlayer(Player* visiblePlayer) {
	const auto visiblePlayerEntity = visiblePlayer->GetSlaveEntity();

	SpawnPlayerPacket packet;
	packet.id = visiblePlayerEntity->GetID();
	memcpy(packet.uuid, visiblePlayerEntity->GetUUID(), sizeof(uuid_t));
	packet.position = visiblePlayerEntity->GetPosition();
	packet.rotation = visiblePlayerEntity->GetRotation();

	visiblePlayerEntity->BuildMetadata();
	
	packet.metadata = visiblePlayerEntity->GetMetadataBlob();

	pNetClient->Invoke(packet);
}

void Player::UnloadChunk(ChunkPosition position) {
	UnloadChunkPacket unloadMsg;
	unloadMsg.x = position.x;
	unloadMsg.z = position.z;

	pNetClient->Invoke(unloadMsg);
}

void Player::LoadChunk(Chunk* pChunk) {
	ChunkDataPacket loadChunkMsg;
	loadChunkMsg.chunk = pChunk;

	pNetClient->Invoke(loadChunkMsg);
}

void Player::AnnounceNewRegion(ChunkPosition newRegionOrigin, ChunkPosition oldRegionOrigin) {
	const auto mapManager = MapManager::GetInstance();

	for (int z = -REGION_SIZE_IN_CHUNKS; z < REGION_SIZE_IN_CHUNKS; z++) {
		for (int x = -REGION_SIZE_IN_CHUNKS; x < REGION_SIZE_IN_CHUNKS; x++) {
			ChunkPosition loadingChunkPosition = {
				newRegionOrigin.x + x,
				newRegionOrigin.z + z
			};

			bool xOuts = loadingChunkPosition.x > oldRegionOrigin.x - REGION_SIZE_IN_CHUNKS
				&& loadingChunkPosition.x < oldRegionOrigin.x + REGION_SIZE_IN_CHUNKS;

			bool zOuts = loadingChunkPosition.z > oldRegionOrigin.z - REGION_SIZE_IN_CHUNKS
				&& loadingChunkPosition.z < oldRegionOrigin.z + REGION_SIZE_IN_CHUNKS;

			if (!zOuts || !xOuts) {
				mapManager->SendChunkAtPosition(
					loadingChunkPosition,
					this
				);
			}

		}
	}
}

void Player::DisposeOldRegion(ChunkPosition newRegionOrigin, ChunkPosition oldRegionOrigin) {
	const auto mapManager = MapManager::GetInstance();

	for (int z = -REGION_SIZE_IN_CHUNKS; z < REGION_SIZE_IN_CHUNKS; z++) {
		for (int x = -REGION_SIZE_IN_CHUNKS; x < REGION_SIZE_IN_CHUNKS; x++) {
			ChunkPosition disposingChunkPosition = {
				oldRegionOrigin.x + x,
				oldRegionOrigin.z + z
			};

			bool xOuts = disposingChunkPosition.x > newRegionOrigin.x - REGION_SIZE_IN_CHUNKS
				&& disposingChunkPosition.x < newRegionOrigin.x + REGION_SIZE_IN_CHUNKS;

			bool zOuts = disposingChunkPosition.z > newRegionOrigin.z - REGION_SIZE_IN_CHUNKS
				&& disposingChunkPosition.z < newRegionOrigin.z + REGION_SIZE_IN_CHUNKS;

			if (!zOuts || !xOuts) {
				mapManager->Dispose(disposingChunkPosition);
				UnloadChunk(disposingChunkPosition);
			}

		}
	}
}

void Player::OnChunkBorderCrossed(ChunkPosition newRegionOrigin, ChunkPosition oldRegionOrigin) {
	AnnounceNewRegion(newRegionOrigin, oldRegionOrigin);
	DisposeOldRegion(newRegionOrigin, oldRegionOrigin);
}
