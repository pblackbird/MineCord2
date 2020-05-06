#pragma once

#include <vector>

#include "../Packets/BaseNetPacket.h"

class DestroyEntitiesPacket : public BaseNetPacket {
public:
	std::vector<entity_id> entities;

public:
	DestroyEntitiesPacket() {
		isCompressed = true;
	}

	virtual void Build(Buffer& dest) override;
};