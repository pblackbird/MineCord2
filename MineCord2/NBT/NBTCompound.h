#pragma once

#include "NBT.h"

class NBTCompound : public NBT {
public:
	std::vector<NBT> tags;
	NBTDataType type = NBTDataType::TAG_Compound;

public:
	virtual void Write(Buffer& dest) override;
	virtual void Read(Buffer& src) override;
};