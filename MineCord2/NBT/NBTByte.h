#pragma once

#include "NBT.h"

class NBTByte : public NBT {
public:
	int8_t value;
	NBTDataType type = NBTDataType::TAG_Byte;

public:
	virtual void Write(Buffer& dest) override;
	virtual void Read(Buffer& src) override;
};