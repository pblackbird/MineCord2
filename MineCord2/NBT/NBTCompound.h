#pragma once

#include "NBT.h"

typedef void(*OnNBTWalkTree_t)(NBT*);

class NBTCompound : public NBT {
public:
	std::vector<NBT*> tags;

public:
	NBTCompound() {
		type = NBTDataType::TAG_Compound;
	}

	virtual void Write(Buffer& dest) override;
	virtual void Read(Buffer& src) override;

	void WalkTree(OnNBTWalkTree_t callback);
};