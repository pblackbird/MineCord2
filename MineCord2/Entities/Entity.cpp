#include "Entity.h"
#include "../Utl.h"

ssize_t Entity::entityIndexCounter = 0;

void Entity::EndMetadataArray() {
	metadataBlob.writeUInt8(0xff);
}

Entity::Entity(const std::string&& uuid) {
	this->uuid = uuid;

	entityId = entityIndexCounter++;
	entityName = "Unnamed creature";
}

Entity::Entity() {
	uuid = Utl::GenerateUUID();

	entityId = entityIndexCounter++;
	entityName = "Unnamed creature";
}

std::vector<uint8_t> Entity::GetMetadataBlob() {
	EndMetadataArray();
	return metadataBlob.getBuffer();
}

void Entity::BuildMetadata() {

	metadataBlob.clear();

	/*AddMetadataEntry<uint8_t>(
		(uint8_t)BaseMetadataIndex::STATE_BITMASK,
		MetadataType::BYTE,
		stateMask
	);*/

	/*AddMetadataEntry<int>(
		(uint8_t)BaseMetadataIndex::AIR,
		MetadataType::VARINT,
		air
	);*/

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