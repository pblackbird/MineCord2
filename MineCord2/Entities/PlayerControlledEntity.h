#pragma once

#include "Entity.h"

enum class PlayerMetadataIndex : uint8_t {
	ADDITIONAL_HEARTS = 11,
	SCORE = 12,
	SKIN_PARTS_BITMASK = 13,
	MAIN_HAND = 14
};

class PlayerControlledEntity : public Entity {
public:
	virtual void OnTick() override;
};