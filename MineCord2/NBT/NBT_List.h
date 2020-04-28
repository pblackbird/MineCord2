#pragma once

#include "NBT.h"

class NBTList : NBT {
public:
    std::vector<NBT> array;
    NBTDataType type = NBTDataType::TAG_List;

public:
    virtual void Write(Buffer& dest) override;
    virtual void Read(Buffer& src) override;
};