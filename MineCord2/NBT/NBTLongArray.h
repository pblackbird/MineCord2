#pragma once

#include "NBT.h"


class NBTLongArray : public NBT
{
public:
    std::vector<int64_t> array;

public:
    NBTLongArray() {
        type = NBTDataType::TAG_Long_Array;
    }

    virtual ~NBTLongArray() override {};

    virtual void Write(Buffer& dest) override;
    virtual void Read(Buffer& src) override;
};
