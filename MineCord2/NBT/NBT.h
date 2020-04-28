#pragma once

#include <cstdint>
#include <string>

#include "../ThirdParty/BufferedIO.h"

enum class NBTDataType : uint8_t {
	TAG_End,
	TAG_Byte,
	TAG_Short,
	TAG_Int,
	TAG_Long,
	TAG_Float,
	TAG_Double,
	TAG_Byte_Array,
	TAG_String,
	TAG_List,
	TAG_Compound,
	TAG_Int_Array,
	TAG_Long_Array
};

class NBT {
protected:
	Buffer buff;

public:
	bool isUnnamed = false;
	std::string name;
	NBTDataType type;

public:
	virtual void Write(Buffer& dest);
	virtual void Read(Buffer& src);
};