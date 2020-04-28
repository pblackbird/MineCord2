#pragma once

#include "NBT.h"

class NBTFloat : public NBT {
public:
	float value;
	NBTDataType type = NBTDataType::TAG_Float;

public:
	virtual void Write(Buffer& dest) override;
	virtual void Read(Buffer& src) override;
};