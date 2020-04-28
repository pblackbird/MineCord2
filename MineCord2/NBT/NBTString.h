#pragma once

#include "NBT.h"

class NBTString : public NBT {
public:
	std::string value;
	NBTDataType type = NBTDataType::TAG_String;

public:
	virtual void Write(Buffer& dest) override;
	virtual void Read(Buffer& src) override;
};