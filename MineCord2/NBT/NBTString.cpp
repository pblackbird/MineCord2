#include "NBTString.h"

void NBTString::Write(Buffer& dest) {
	NBT::Write(dest);

	dest.writeUInt16_LE(value.length());
	dest.writeStr(value);
}

void NBTString::Read(Buffer& src) {
	NBT::Read(src);

	uint16_t length = src.readUInt16_LE();
	value = src.readStr(length);
}
