#pragma once

#include "NBT.h"


class NBTIntArray : public NBT
{
public:
    std::vector<int> array;

public:
    NBTIntArray() {
        type = NBTDataType::TAG_Int_Array;
    }

    virtual ~NBTIntArray() override {};

    virtual void Write(Buffer& dest) override;
    virtual void Read(Buffer& src) override;
};
