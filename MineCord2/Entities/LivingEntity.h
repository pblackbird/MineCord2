#pragma once

#include "Entity.h"

enum class LivingMetadataIndex : uint8_t {
	//HAND_BITMASK = 5,
	HEALTH = 6,
	POTION_EFFECT_COLOR = 7,
	NUMBER_OF_ARROWS = 9
};

class LivingEntity : public Entity {

public:
	uint8_t handBitmask = 0;
	float health = 1.0f;
	int potionEffectColor = 0;
	bool isPotionEffectAmbient = false;
	int numberOfArrows = 0;

public:
	void BuildMetadata() override;
};
