#include "NBTShort.h"

void NBTShort::Write(Buffer& dest) {
	type = NBTDataType::TAG_Short;

	NBT::Write(dest);

	dest.writeInt16_BE(value);
}

void NBTShort::Read(Buffer& src) {
	NBT::Read(src);

	value = src.readInt16_BE();
}
