#include "NBTLong.h"

void NBTLong::Write(Buffer& dest) {
	NBT::Write(dest);

	dest.writeInt64_BE(value);
}

void NBTLong::Read(Buffer& src) {
	NBT::Read(src);

	value = src.readInt64_BE();
}
