#include "NBTInt.h"

void NBTInt::Write(Buffer& dest) {
	type = NBTDataType::TAG_Int;

	NBT::Write(dest);

	dest.writeInt32_BE(value);
}

void NBTInt::Read(Buffer& src) {
	NBT::Read(src);

	value = src.readInt32_BE();
}
