#pragma once

#include "NBT.h"

class NBTDouble : public NBT {
public:
	double value;
	NBTDataType type = NBTDataType::TAG_Double;

public:
	virtual void Write(Buffer& dest) override;
	virtual void Read(Buffer& src) override;
};