#pragma once

#include <cassert>

#include "LivingEntity.h"
#include "../Network/MinecraftNetworkClient.h"

enum class PlayerMetadataIndex : uint8_t {
	ADDITIONAL_HEARTS = 11,
	SCORE = 12,
	SKIN_PARTS_BITMASK = 13,
	MAIN_HAND = 14
};

class PlayerEntity : public LivingEntity {
public:
	float additionalHearts = 0.0f;
	int score = 0;
	uint8_t skinPartsBitmask = 0;
	uint8_t mainHand = 1;

public:
	PlayerEntity(const std::string&& uuid);

	virtual void BuildMetadata() override;

	virtual void OnTick() override;
	virtual void OnCreate() override;
	virtual void OnDestroy() override;
};