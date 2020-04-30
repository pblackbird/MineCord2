#include "NBTFloat.h"

void NBTFloat::Write(Buffer& dest) {
	type = NBTDataType::TAG_Float;

	NBT::Write(dest);

	dest.writeFloat_BE(value);
}

void NBTFloat::Read(Buffer& src) {
	NBT::Read(src);

	value = src.readFloat_BE();
}
