#include "Entity.h"
#include "../GamePackets/DestroyEntitiesPacket.h"
#include "../GamePackets/SetEntityPositionRotationPacket.h"
#include "../GamePackets/EntityMovementPacket.h"
#include "../Utl.h"
#include "../World/PrimaryWorld.h"

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

void Entity::SyncEntity() {
	const auto player = PrimaryWorld::GetInstance()->GetPlayerBySlaveId(entityId);

	EntityMovementPacket movePacket;
	movePacket.id = entityId;

	//PrimaryWorld::GetInstance()->BroadcastMessage(movePacket, player);

	AngleStep steps = Transformable::GetStepByAngle(rotation);

	Point3D deltaPosition = {
		lastPosition.x,
		lastPosition.y,
		lastPosition.z
	};

	SetEntityPositionRotationPacket setTransform;
	setTransform.isOnGround = true;
	setTransform.id = entityId;
	setTransform.angle = steps;
	setTransform.deltaPosition = deltaPosition;

	PrimaryWorld::GetInstance()->BroadcastMessage(setTransform, player);

	lastPosition = { 0.0, 0.0, 0.0 };
}

void Entity::OnTick() {
	
}

void Entity::OnDestroy() {
	DestroyEntitiesPacket destroyMsg;
	destroyMsg.entities.push_back(entityId);

	PrimaryWorld::GetInstance()->BroadcastMessage(destroyMsg);
}

std::vector<uint8_t> Entity::GetMetadataBlob() {
	EndMetadataArray();
	return metadataBlob.getBuffer();
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