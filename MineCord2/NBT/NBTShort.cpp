#include "NBTShort.h"

void NBTShort::Write(Buffer& dest) {
	NBT::Write(dest);

	dest.writeInt16_LE(value);
}

void NBTShort::Read(Buffer& src) {
	NBT::Read(src);

	value = src.readInt16_LE();
}
