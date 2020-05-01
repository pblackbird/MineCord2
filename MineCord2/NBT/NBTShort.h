#pragma once

#include "NBT.h"

class NBTShort : public NBT {
public:
	int16_t value;

public:
	NBTShort() {
		type = NBTDataType::TAG_Short;
	}

	virtual ~NBTShort() override {};

	virtual void Write(Buffer& dest) override;
	virtual void Read(Buffer& src) override;
};