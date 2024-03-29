#include "NBT_List.h"

NBTList::~NBTList() {
    for (auto element : array) {
        delete element;
    }
}

void NBTList::Write(Buffer& dest) {
  type = NBTDataType::TAG_List;

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
    NBT *currentTag = NBT::ReadNBTSafely(src);
    currentTag->isUnnamed = true;

    array.push_back(currentTag);
  }
}
