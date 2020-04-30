#include "NBTByte.h"

void NBTByte::Write(Buffer& dest) {
	type = NBTDataType::TAG_Byte;

	NBT::Write(dest);

	dest.writeInt8(value);
}

void NBTByte::Read(Buffer& src) {
	NBT::Read(src);

	value = src.readInt8();
}
