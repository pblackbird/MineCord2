#include "NBTLongArray.h"

void NBTLongArray::Write(Buffer& dest) {
  NBT::Write(dest);

  dest.writeInt32_BE((int32_t)array.size());

  for (const auto byte : array) {
    dest.writeInt64_BE(byte);
  }
}

void NBTLongArray::Read(Buffer& src) {
  NBT::Read(src);

  int32_t arraySize = src.readInt32_BE();
  array.resize(arraySize);

  for (int i = 0; i < arraySize; i++) {
    array.push_back(src.readInt64_BE());
  }
}
