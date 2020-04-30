#pragma once

#include "../Packets/BaseNetPacket.h"
#include "../Map/Chunk.h"

class ChunkDataPacket : public BaseNetPacket {
public:
	Chunk chunk;

public:
	virtual void Build(Buffer& dest) override;
};