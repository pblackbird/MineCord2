#pragma once

#include "NBT.h"

class NBTFloat : public NBT {
public:
	float value;

public:
	NBTFloat() {
		type = NBTDataType::TAG_Float;
	}

	virtual void Write(Buffer& dest) override;
	virtual void Read(Buffer& src) override;
};