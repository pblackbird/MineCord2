#pragma once

#include "NBT.h"

class NBTInt : public NBT {
public:
	int32_t value;
	NBTDataType type = NBTDataType::TAG_Int;

public:
	virtual void Write(Buffer& dest) override;
	virtual void Read(Buffer& src) override;
};