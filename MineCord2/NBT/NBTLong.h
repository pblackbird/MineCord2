#pragma once

#include "NBT.h"

class NBTLong : public NBT {
public:
	int64_t value;
	NBTDataType type = NBTDataType::TAG_Int;

public:
	virtual void Write(Buffer& dest) override;
	virtual void Read(Buffer& src) override;
};