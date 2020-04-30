#include "NBTIntArray.h"

void NBTIntArray::Write(Buffer& dest) {
  type = NBTDataType::TAG_Int_Array;

  NBT::Write(dest);

  dest.writeInt32_BE((int32_t)array.size());

  for (const auto byte : array) {
    dest.writeInt32_BE(byte);
  }
}

void NBTIntArray::Read(Buffer& src) {
  NBT::Read(src);

  int32_t arraySize = src.readInt32_BE();
  array.resize(arraySize);

  for (int i = 0; i < arraySize; i++) {
    array.push_back(src.readInt32_BE());
  }
}
