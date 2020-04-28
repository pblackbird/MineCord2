#include "NBT.h"

void NBT::Write(Buffer& dest) {
	dest.writeUInt8((uint8_t)type);
	dest.writeUInt16_LE(name.length());
	dest.writeStr(name);
}

void NBT::Read(Buffer& src) {
	type = static_cast<NBTDataType>(src.readUInt8());

	uint64_t nameLength = src.readUInt16_LE();
	name = src.readStr(nameLength);
}
