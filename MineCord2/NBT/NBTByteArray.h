#pragma once

#include "NBT.h"

class NBTByteArray : public NBT {
public:
	std::vector<int8_t> array;

public:
	NBTByteArray() {
		type = NBTDataType::TAG_Byte_Array;
	}

	virtual ~NBTByteArray() override {};

	virtual void Write(Buffer& dest) override;
	virtual void Read(Buffer& src) override;
};