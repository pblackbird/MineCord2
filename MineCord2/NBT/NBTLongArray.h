#pragma once

#include "NBT.h"


class NBTLongArray : public NBT
{
public:
    std::vector<long> array;
    NBTDataType type = NBTDataType::TAG_Long_Array;

public:
    virtual void Write(Buffer& dest) override;
    virtual void Read(Buffer& src) override;
};
