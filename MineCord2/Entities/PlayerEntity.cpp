#include "PlayerEntity.h"
#include "../GamePackets/ChunkDataPacket.h"
#include "../World/PrimaryWorld.h"
#include "../Map/TestMapManager.h"
#include "../GamePackets/PlayerInfoPacket.h"
#include <functional>
#include <string.h>

PlayerEntity::PlayerEntity(const std::string uuid) : LivingEntity() {
	uuid_parse(uuid.c_str(), this->uuid);
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
	const auto player = PrimaryWorld::GetInstance()->GetPlayerBySlaveId(entityId);
	assert(player);
	
	position = { 0, 193, 0 };

	player->Join(GameMode::SURVIVAL);
	player->SetTransform(
		position,
		rotation
	);
	
	for (int chunkX = 0; chunkX < 5; chunkX++) {
		for (int chunkZ = 0; chunkZ < 5; chunkZ++) {
			TestMapManager::GetInstance()->SendRegionAtPosition({ chunkX, chunkZ }, player);
		}
	}

	player->SetPlayerPositionChunk({ 0, 0 });

	std::vector<PlayerListEntry> playersList;
	std::function<void(Player* player)> pushPlayer = [&playersList](Player* existPlayer) {
		PushPlayer(playersList, existPlayer);
	};
	
	PrimaryWorld::GetInstance()->EnumeratePlayers(pushPlayer);

	PrimaryWorld::GetInstance()->EnumeratePlayers([player](Player* currentPlayer) {
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

	player->ControlTabMenu(
		PlayerInfoAction::ADD_PLAYER,
		playersList
	);

	PrimaryWorld::GetInstance()->EnumeratePlayers([player](Player* currentPlayer) {
		if (player == currentPlayer) {
			return;
		}

		player->SpawnVisiblePlayer(currentPlayer);
	});
}

void PlayerEntity::OnDestroy() {
	const auto player = PrimaryWorld::GetInstance()->GetPlayerBySlaveId(entityId);
	assert(player);

	PlayerListEntry playerToRemove;
	memcpy(playerToRemove.uuid, uuid, sizeof(uuid_t));

	PrimaryWorld::GetInstance()->EnumeratePlayers([playerToRemove, player](Player* currentPlayer) {
		if (currentPlayer == player) {
			return;
		}

		currentPlayer->ControlTabMenu(PlayerInfoAction::REMOVE_PLAYER, { 
			playerToRemove 
		});
	});
}