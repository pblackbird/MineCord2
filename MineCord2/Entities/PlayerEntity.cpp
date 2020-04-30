#include "PlayerEntity.h"
#include "../GamePackets/ChunkDataPacket.h"
#include "../World/PrimaryWorld.h"
#include "../Map/TestMapManager.h"

PlayerEntity::PlayerEntity(const std::string&& uuid) : LivingEntity() {
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

void PlayerEntity::OnCreate() {
	const auto player = PrimaryWorld::GetInstance()->GetPlayerBySlaveId(entityId);
	assert(player);
	
	player->Join();
	player->SetTransform(
		position,
		rotation
	);
}

void PlayerEntity::OnDestroy() {

}
