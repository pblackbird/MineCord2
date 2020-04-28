#pragma once

#include "NBT.h"


class NBTIntArray : NBT
{
public:
  std::vector<int> array;
  NBTDataType type = NBTDataType::TAG_Int_Array;

public:
  virtual void Write(Buffer& dest) override;
  virtual void Read(Buffer& src) override;
}
