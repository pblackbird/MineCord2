#pragma once

#include "NBT.h"

class NBTByteArray : public NBT {
public:
	std::vector<int8_t> array;
	NBTDataType type = NBTDataType::TAG_Byte_Array;

public:
	virtual void Write(Buffer& dest) override;
	virtual void Read(Buffer& src) override;
};