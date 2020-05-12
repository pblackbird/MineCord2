#include "PlayerEntity.h"
#include "../GamePackets/ChunkDataPacket.h"
#include "../World/PrimaryWorld.h"
#include "../Map/MapManager.h"
#include "../GamePackets/PlayerInfoPacket.h"
#include "../GamePackets/SetEntityRotationPacket.h"
#include "../GamePackets/ServerChatSayPacket.h"
#include <functional>
#include <string.h>

PlayerEntity::PlayerEntity(const std::string uuid) : LivingEntity() {
	uuid_parse(uuid.c_str(), this->uuid);
	isPlayer = true;
}

void PlayerEntity::BuildMetadata() {
	LivingEntity::BuildMetadata();

	AddMetadataEntry<float>(
		(uint8_t)PlayerMetadataIndex::ADDITIONAL_HEARTS,
		MetadataType::FLOAT,
		additionalHearts
	);

	AddMetadataEntry<int>(
		(uint8_t)PlayerMetadataIndex::SCORE,
		MetadataType::VARINT,
		score
	);

	AddMetadataEntry<uint8_t>(
		(uint8_t)PlayerMetadataIndex::SKIN_PARTS_BITMASK,
		MetadataType::BYTE,
		skinPartsBitmask
	);

	AddMetadataEntry<uint8_t>(
		(uint8_t)PlayerMetadataIndex::MAIN_HAND,
		MetadataType::BYTE,
		mainHand
	);
}

void PlayerEntity::OnTick() {
	Entity::OnTick();
}

void PushPlayer(std::vector<PlayerListEntry>& list, Player* existPlayer) {
	const auto playerSlave = existPlayer->GetSlaveEntity();

	PlayerListEntry playerListEntry;
	
	memcpy(playerListEntry.uuid, playerSlave->GetUUID(), sizeof(uuid_t));
	playerListEntry.hasDisplayName = /* HARD CODE */ true;
	playerListEntry.ping = /* HARD CODE */ 0;
	playerListEntry.gamemode = /* HARD CODE */ GameMode::SURVIVAL;

	PlayerPropertyListEntry textureProp;
	textureProp.propertyName = "textures";
	textureProp.value = "";
	textureProp.isSigned = false;
	textureProp.signature = "";

	playerListEntry.properties = {
		textureProp
	};

	playerListEntry.name = playerSlave->GetName();
	if (playerListEntry.hasDisplayName) {
		playerListEntry.displayName = playerSlave->GetName();
	}

	list.push_back(playerListEntry);
}

void PlayerEntity::OnCreate() {
	const auto world = PrimaryWorld::GetInstance();

	const auto player = world->GetPlayerBySlaveId(entityId);
	assert(player);
	
	position = { 400, 193, 400 };

	const auto playerChunk = player->GetSlaveEntity()->GetCurrentChunkPosition();

	MapManager::GetInstance()->OnChunkBorderCrossed(
		playerChunk,
		playerChunk,
		this
	);

	// spawn player in world locally for this player
	player->Join(GameMode::SURVIVAL);

	player->SetTransform(
		position,
		rotation
	);

	// Fill new player's tab menu with already connected players
	std::vector<PlayerListEntry> playersList;
	std::function<void(Player* player)> pushPlayer = [&playersList](Player* existPlayer) {
		PushPlayer(playersList, existPlayer);
	};
	
	world->EnumeratePlayers(pushPlayer);

	// Announce new player to already connected players and spawn new player's entity for them
	world->EnumeratePlayers([player](Player* currentPlayer) {
		if (player == currentPlayer) {
			return;
		}

		std::vector<PlayerListEntry> tmp;
		PushPlayer(tmp, player);

		currentPlayer->ControlTabMenu(
			PlayerInfoAction::ADD_PLAYER,
			tmp
		);

		currentPlayer->SpawnVisiblePlayer(player);
	});

	// Send crafted tab menu to new player
	player->ControlTabMenu(
		PlayerInfoAction::ADD_PLAYER,
		playersList
	);

	// Spawn visible player entities for new player
	world->EnumeratePlayers([player](Player* currentPlayer) {
		if (player == currentPlayer) {
			return;
		}

		player->SpawnVisiblePlayer(currentPlayer);
	});

	// welcome message :3
	ServerChatSayPacket say;
	say.m_json = "{\"text\": \"Player " + player->GetNetClient()->GetUsername() + " has joined the game\"}";

	world->BroadcastMessage(say);
}

void PlayerEntity::OnDestroy() {
	const auto world = PrimaryWorld::GetInstance();

	const auto player = world->GetPlayerBySlaveId(entityId);
	assert(player);

	PlayerListEntry playerToRemove;
	memcpy(playerToRemove.uuid, uuid, sizeof(uuid_t));

	// remove disconnected player from other's player list
	world->EnumeratePlayers([playerToRemove, player](Player* currentPlayer) {
		if (currentPlayer == player) {
			return;
		}

		currentPlayer->ControlTabMenu(PlayerInfoAction::REMOVE_PLAYER, { 
			playerToRemove 
		});
	});

	Entity::OnDestroy();
}