#pragma once

#include "NBT.h"

class NBTList : public NBT {
public:
    std::vector<NBT*> array;

public:
    NBTList() {
        type = NBTDataType::TAG_List;
    }

    virtual void Write(Buffer& dest) override;
    virtual void Read(Buffer& src) override;
};