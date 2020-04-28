#pragma once

#include "NBT.h"

class NBTShort : public NBT {
public:
	int16_t value;
	NBTDataType type = NBTDataType::TAG_Short;

public:
	virtual void Write(Buffer& dest) override;
	virtual void Read(Buffer& src) override;
};