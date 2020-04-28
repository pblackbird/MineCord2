#include "NBT.h"

void NBT::Write(Buffer& dest) {
	dest.writeUInt8((uint8_t)type);

  if (!isUnnamed) {
  	dest.writeUInt16_LE((uint16_t)name.length());
  	dest.writeStr(name);
  }
}

void NBT::Read(Buffer& src) {
	type = static_cast<NBTDataType>(src.readUInt8());

  if (!isUnnamed) {
  	uint16_t nameLength = src.readUInt16_LE();
  	name = src.readStr(nameLength);
  }
}
