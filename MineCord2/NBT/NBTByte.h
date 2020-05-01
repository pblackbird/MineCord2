#pragma once

#include "NBT.h"

class NBTByte : public NBT {
public:
	int8_t value;

public:
	NBTByte() {
		type = NBTDataType::TAG_Byte;
	}

	virtual ~NBTByte() override {};

	virtual void Write(Buffer& dest) override;
	virtual void Read(Buffer& src) override;
};