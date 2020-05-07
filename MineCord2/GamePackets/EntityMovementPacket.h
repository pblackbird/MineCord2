#pragma once

#include "../Packets/BaseNetPacket.h"

class EntityMovementPacket : public BaseNetPacket {
public:
	entity_id id;

public:
	EntityMovementPacket() {
		isCompressed = true;
	}

	virtual void Build(Buffer& dest) override;
};