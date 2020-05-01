#pragma once

#include "NBT.h"

class NBTLong : public NBT {
public:
	int64_t value;

public:
	NBTLong() {
		type = NBTDataType::TAG_Long;
	}

	virtual ~NBTLong() override {};

	virtual void Write(Buffer& dest) override;
	virtual void Read(Buffer& src) override;
};