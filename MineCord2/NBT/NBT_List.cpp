#include "NBT_List.h"

void NBTList::Write(Buffer& dest) {
  NBT::Write(dest);

  dest.writeInt32_BE((int32_t)array.size());

  for (const auto byte : array) {
    NBT currentTag;
    currentTag.isUnnamed = true;
    currentTag.Write(dest);
  }
}

void NBTList::Read(Buffer& src) {
  NBT::Read(src);

  int32_t arraySize = src.readInt32_BE();
  array.resize(arraySize);

  for (int i = 0; i < arraySize; i++) {
    NBT currentTag;
    currentTag.isUnnamed = true;
    currentTag.Read(src);
    array.push_back(currentTag);
  }
}
