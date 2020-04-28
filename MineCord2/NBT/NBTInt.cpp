#include "NBTInt.h"

void NBTInt::Write(Buffer& dest) {
	NBT::Write(dest);

	dest.writeInt32_LE(value);
}

void NBTInt::Read(Buffer& src) {
	NBT::Read(src);

	value = src.readInt32_LE();
}
