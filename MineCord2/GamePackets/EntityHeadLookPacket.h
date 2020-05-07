#pragma once

#include "../Packets/BaseNetPacket.h"
#include "../Transformable.h"

class EntityHeadLookPacket : public BaseNetPacket {
public:
	entity_id id;
	uint8_t headYaw;

public:
	EntityHeadLookPacket() {
		isCompressed = true;
	}

	virtual void Build(Buffer& dest) override;
};