#include "NBTString.h"

void NBTString::Write(Buffer& dest) {
	NBT::Write(dest);

	dest.writeUInt16_BE((uint16_t)value.length());
	dest.writeStr(value);
}

void NBTString::Read(Buffer& src) {
	NBT::Read(src);

	uint16_t length = src.readUInt16_BE();
	value = src.readStr(length);
}
