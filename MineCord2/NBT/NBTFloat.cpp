#include "NBTFloat.h"

void NBTFloat::Write(Buffer& dest) {
	NBT::Write(dest);

	dest.writeFloat_LE(value);
}

void NBTFloat::Read(Buffer& src) {
	NBT::Read(src);

	value - src.readFloat_LE();
}
