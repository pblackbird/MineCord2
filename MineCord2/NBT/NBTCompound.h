#pragma once

#include "NBT.h"

typedef void(*OnNBTWalkTree_t)(NBT*);

class NBTCompound : public NBT {
public:
	std::vector<NBT*> tags;
	NBTDataType type = NBTDataType::TAG_Compound;

public:
	virtual void Write(Buffer& dest) override;
	virtual void Read(Buffer& src) override;

	void WalkTree(OnNBTWalkTree_t callback);
};