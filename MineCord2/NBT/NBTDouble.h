#pragma once

#include "NBT.h"

class NBTDouble : public NBT {
public:
	double value;

public:
	NBTDouble() {
		type = NBTDataType::TAG_Double;
	}

	virtual void Write(Buffer& dest) override;
	virtual void Read(Buffer& src) override;
};