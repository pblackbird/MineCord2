#include "LivingEntity.h"

void LivingEntity::BuildMetadata() {
	Entity::BuildMetadata();

	AddMetadataEntry<float>(
		(uint8_t)LivingMetadataIndex::HEALTH,
		MetadataType::FLOAT,
		health
	);

	AddMetadataEntry<int>(
		(uint8_t)LivingMetadataIndex::POTION_EFFECT_COLOR,
		MetadataType::VARINT,
		potionEffectColor
	);

	AddMetadataEntry<int>(
		(uint8_t)LivingMetadataIndex::NUMBER_OF_ARROWS,
		MetadataType::VARINT,
		numberOfArrows
	);

}
