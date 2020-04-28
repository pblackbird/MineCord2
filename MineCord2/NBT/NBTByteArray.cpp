#include "NBTByteArray.h"

void NBTByteArray::Write(Buffer& dest) {
	NBT::Write(dest);

	dest.writeInt32_BE(array.size());

	for (const auto byte : array) {
		dest.writeInt8(byte);
	}
}

void NBTByteArray::Read(Buffer& src) {
	NBT::Read(src);

	int32_t arraySize = src.readInt32_BE();
	array.resize(arraySize);

	for (int i = 0; i < arraySize; i++) {
		array.push_back(src.readInt8());
	}
}
