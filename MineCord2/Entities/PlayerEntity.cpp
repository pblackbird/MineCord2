#include "PlayerEntity.h"
#include "../GamePackets/ChunkDataPacket.h"
#include "../World/PrimaryWorld.h"
#include "../Map/TestMapManager.h"
#include "../GamePackets/PlayInfoPacket.h"
#include <functional>

PlayerEntity::PlayerEntity(const std::string uuid) : LivingEntity() {
	this->uuid = uuid;
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

	playerListEntry.uuid = playerSlave->GetUUID();
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
	
	position = { 0, 200, 0 };

	player->Join(GameMode::SURVIVAL);
	player->SetTransform(
		position,
		rotation
	);
	
	for (int chunkX = 0; chunkX < 1; chunkX++) {
		//for (int chunkZ = 0; chunkZ < 1; chunkZ++) {
			TestMapManager::GetInstance()->SendRegionAtPosition({ chunkX, 0 }, player);
		//}
	}

	player->SetPlayerPositionChunk({ 0, 0 });

	std::vector<PlayerListEntry> playersList;
	std::function<void(Player* player)> pushPlayer = [&playersList](Player* existPlayer) {
		PushPlayer(playersList, existPlayer);
	};
	
	PrimaryWorld::GetInstance()->EnumeratePlayers(pushPlayer);

	PlayerInfoPacket infoPacket;
	infoPacket.action = PlayerInfoAction::ADD_PLAYER;
	infoPacket.uuid = uuid;
	infoPacket.players = playersList;

	player->GetNetClient()->Invoke(infoPacket);

	infoPacket.players = {};
	PushPlayer(infoPacket.players, player);

	PrimaryWorld::GetInstance()->BroadcastMessage(infoPacket, player);
}

void PlayerEntity::OnDestroy() {

}