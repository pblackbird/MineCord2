#include "NBTDouble.h"

void NBTDouble::Write(Buffer& dest) {
	type = NBTDataType::TAG_Double;

	NBT::Write(dest);

	dest.writeDouble_BE(value);
}

void NBTDouble::Read(Buffer& src) {
	NBT::Read(src);

	value = src.readDouble_BE();
}
