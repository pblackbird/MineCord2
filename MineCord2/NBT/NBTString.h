#pragma once

#include "NBT.h"

class NBTString : public NBT {
public:
	std::string value;

public:
	NBTString() {
		type = NBTDataType::TAG_String;
	}

	virtual ~NBTString() override {};

	virtual void Write(Buffer& dest) override;
	virtual void Read(Buffer& src) override;
};