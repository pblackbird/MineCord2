#include "Entity.h"
#include "../GamePackets/DestroyEntitiesPacket.h"
#include "../GamePackets/SetEntityPositionRotationPacket.h"
#include "../GamePackets/EntityHeadLookPacket.h"
#include "../GamePackets/EntityMovementPacket.h"
#include "../Utl.h"
#include "../World/PrimaryWorld.h"
#include "../Map/MapManager.h"

entity_id Entity::entityIndexCounter = 0;

void Entity::EndMetadataArray() {
	metadataBlob.writeUInt8(0xff);
}

Entity::Entity(const std::string&& uuid) {
	uuid_parse(uuid.c_str(), this->uuid);

	entityId = entityIndexCounter++;
	entityName = "Unnamed creature";
}

Entity::Entity() {
	uuid_parse(Utl::GenerateUUID().c_str(), this->uuid);

	entityId = entityIndexCounter++;
	entityName = "Unnamed creature";
}

void Entity::OnMove(Point3D newPos) {
	const auto currentChunkPos = GetCurrentChunkPosition();
	const auto player = PrimaryWorld::GetInstance()->GetPlayerBySlaveId(entityId);

	const auto dir = movementDirection.GetDirection();

	lastKnownPosition = {
		(newPos.x * 32 - position.x * 32) * 128,
		(newPos.y * 32 - position.y * 32) * 128,
		(newPos.z * 32 - position.z * 32) * 128,
	};

	Move(dir.x, dir.y, dir.z);

	if (currentChunkPos.x != lastChunkPosition.x || currentChunkPos.z != lastChunkPosition.z) {
		if (player) {
			MapManager::GetInstance()->OnChunkBorderCrossed(currentChunkPos, lastChunkPosition, player);
			lastChunkPosition = currentChunkPos;
		}
	}
}

void Entity::OnNetSync() {
	const auto world = PrimaryWorld::GetInstance();
	const auto player = world->GetPlayerBySlaveId(entityId);

	AngleStep steps = Transformable::GetStepByAngle(rotation);

	SetEntityPositionRotationPacket setTransform;
	setTransform.isOnGround = true;
	setTransform.id = entityId;
	setTransform.angle = steps;
	setTransform.deltaPosition = lastKnownPosition;
	world->BroadcastMessage(setTransform, player);

	EntityHeadLookPacket headYawPacket;
	headYawPacket.id = entityId;
	headYawPacket.headYaw = steps.yaw;
	world->BroadcastMessage(headYawPacket, player);
}

void Entity::OnTick() {
	
}

void Entity::OnDestroy() {
	// destroy disconnected player's entity for other players
	DestroyEntitiesPacket destroyMsg;
	destroyMsg.entities.push_back(entityId);

	PrimaryWorld::GetInstance()->BroadcastMessage(destroyMsg);
}

std::vector<uint8_t> Entity::GetMetadataBlob() {
	EndMetadataArray();
	return metadataBlob.getBuffer();
}

ChunkPosition Entity::GetCurrentChunkPosition() {
	return {
		(int32_t)(position.x) / 16,
		(int32_t)(position.z) / 16
	};
}

void Entity::BuildMetadata() {

	metadataBlob.clear();

	AddStringMetadataEntry(
		(uint8_t)BaseMetadataIndex::CUSTOMNAME,
		customName
	);

	AddMetadataEntry<bool>(
		(uint8_t)BaseMetadataIndex::IS_CUSTOMNAME_VISIBLE,
		MetadataType::BOOLEAN,
		isCustomNameVisible
	);

	AddMetadataEntry<bool>(
		(uint8_t)BaseMetadataIndex::IS_SILENT,
		MetadataType::BOOLEAN,
		isSilent
	);

}