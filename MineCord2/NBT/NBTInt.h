#pragma once

#include "NBT.h"

class NBTInt : public NBT {
public:
	int32_t value;

public:
	NBTInt() {
		type = NBTDataType::TAG_Int;
	}

	virtual void Write(Buffer& dest) override;
	virtual void Read(Buffer& src) override;
};